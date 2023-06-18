/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:55:39 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 00:13:56 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(int status)
{
	int	exit_status;
	
	if (g_global_exit.exit > 0)
	{
		if (g_global_exit.exit == 1)
			g_global_exit.exit_status = status / 256;
		g_global_exit.exit++;
		return;
	}
	// if (status == 1 || status == 2 || status == 127 || status == 126 || status == 131 || status == 130)
	// 	return ;
	if (status == 258)
	{
		g_global_exit.exit_status = 2;
		return;
	}
	if (WIFEXITED(status)) 
	{
		exit_status = WEXITSTATUS(status);
    }
	else if (WIFSIGNALED(status))
	{
		if (status == 2)
		{
			ft_printf(1, "\n");
			g_global_exit.exit_status = 130;
			return;
		}
		else if (status == 3)
		{
			ft_printf(1, "Quit: 3\n");
			g_global_exit.exit_status = 131;
			return;
		}
	}
	// return (exit_status);
	g_global_exit.exit_status = exit_status;
}

int	check_slash(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return -1;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	ft_free(char **ret, int k)
{
	int	j;

	j = 0;
	while (j < k)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

char	**env_arr(t_list_env **envr)
{
	t_list_env *env;
	char		**arr;
	char		*tmp;
	int			i;
	int			len;

	i = 0;
	env = *envr;
	len = env_size(*envr);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	while (env != NULL)
	{
		tmp = ft_strjoin(env->data.key, "=");
		arr[i] = ft_strjoin(tmp, env->data.value);
		if (!arr[i])
		{
			ft_free(arr, i);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	execute(t_list_env **new_env, char **cmd_parsed)
{
	char	*pathname;
	char	**value;
	int		status;
	int		id;
	int		i;
	struct stat fileStat;

	if (!cmd_parsed || !cmd_parsed[0])
		return ;
	// if (g_global_exit.size == 1)
	// 	id = fork();
	// else
	// 	id = 0;
	i = 0;
	int j = 0;
	id = fork();
	if (id == 0)
	{
		rl_catch_signals = 1;
		g_global_exit.killed = 2;
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		stat(cmd_parsed[0], &fileStat);
		if (!ft_strcmp(cmd_parsed[0], "."))
		{
			// printf("minishell : .: filename argument required .: usage: . filename [arguments]\n");
			ft_putstr_fd("minishell : .: filename argument required .: usage: . filename [arguments]\n", 2);
			g_global_exit.exit_status = 2;
			return ;	
		}
		else if (S_ISDIR(fileStat.st_mode) && ft_strcmp(cmd_parsed[0], ".."))
		{
			// ft_putstr_fd("minishell : is a directory\n", 2);
			ft_printf(2, "minishell : %s: is a directory\n", cmd_parsed[0]);
		}
		else if (!check_slash(cmd_parsed[0]))
		{
			if (!access(cmd_parsed[0], F_OK) && !access(cmd_parsed[0], X_OK))
				execve(cmd_parsed[0], cmd_parsed, env_arr(new_env));
			else
			{
				// ft_putstr_fd("minishell : No such file or directory\n", 2);
				ft_printf(2, "minishell : %s: No such file or directory\n", cmd_parsed[0]);
				g_global_exit.exit_status = 127;
				return;
			}
		}
		else
		{
			// if (ft_strcmp(cmd_parsed[0], "ls"))
			value = get_path_value(new_env);
			if (!value)
			{
				ft_printf(2, "minishell : %s: no such file or directory\n", cmd_parsed[0]);
				g_global_exit.exit_status = 127;
				return ;
			}
			while (value[i] != NULL)
			{
				pathname = ft_strjoin(value[i], "/");
				pathname = ft_strjoin(pathname, cmd_parsed[0]);
				if (!access(pathname, F_OK) && access(pathname, X_OK))
				{
					ft_putstr_fd("minishell: Permission denied\n", 2);
					// printf("minishell: %s: Permission denied\n", pathname);
					g_global_exit.exit_status = 126;
					return;
				}
				else
				{
					execve(pathname, cmd_parsed, env_arr(new_env));
				}
				i++;
			}
			ft_putstr_fd("minishell: command not found\n", 2);
			g_global_exit.exit_status = 127;
		}
		exit(g_global_exit.exit_status);
	}
	waitpid(-1, &status, 0);
	exit_status(status);
}