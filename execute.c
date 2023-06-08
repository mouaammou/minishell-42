/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:55:39 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/08 05:26:08 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(int status)
{
	int	exit_status;

	if (WIFEXITED(status)) 
	{
		exit_status = WEXITSTATUS(status);
    }
	else if (WIFSIGNALED(status))
	{
		if (status == 2)
		{
			// ft_printf("^C\n");
			global_exit.exit_status = 130;
			// ft_kill(global_exit);
			return;
		}
		else if (status == 3)
		{
			ft_printf("Quit: 3\n");
			global_exit.exit_status = 131;
			return;
		}
	}
	// return (exit_status);
	global_exit.exit_status = exit_status;
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

	if (!cmd_parsed || !cmd_parsed[0])
		return ;
	if (global_exit.size == 1)
		id = fork();
	else
		id = 0;
	i = 0;
	int j = 0;
	if (id == 0)
	{
		global_exit.killed = 2;
		signal(SIGQUIT, SIG_DFL);
		// TODO: handle redirections
		// dup2(cmd->fdout, STDOUT);
		// dup2(cmd->fdin, STDIN)
		if (!check_slash(cmd_parsed[0]))
		{
			// printf("ha fin dkhal");
			if (!access(cmd_parsed[0], F_OK) && !access(cmd_parsed[0], X_OK))
				execve(cmd_parsed[0], cmd_parsed, env_arr(new_env));
			else
				printf("bsh!!!!");
		}
		else
		{
			// printf("la dkhal hna");
			value = get_path_value(new_env);
			while (value[i] != NULL)
			{
				pathname = ft_strjoin(value[i], "/");
				pathname = ft_strjoin(pathname, cmd_parsed[0]);
				if (!access(pathname, F_OK) && access(pathname, X_OK))
				{
					printf("minishell: %s: Permission denied\n", pathname);
					global_exit.exit_status = 126;
					return;
				}
				else
					execve(pathname, cmd_parsed, env_arr(new_env));
				i++;
			}
			if (access(cmd_parsed[0], F_OK))
			{
				// stat check if directory appear this error in dislay : "bash: ./test: is a directory"
				printf("minishell: %s: command not found\n", cmd_parsed[0]);
				global_exit.exit_status = 127;
				// exit(global_exit.exit_status);
			}
		}
		exit(global_exit.exit_status);
		// perror("bash: ./test:  ");
	}
	waitpid(-1, &status, 0);
	exit_status(status);
	// printf("status=%d, exit_status_glob=%d\n",status, global_exit.exit_status);
	// return (exit_status(status));
}
