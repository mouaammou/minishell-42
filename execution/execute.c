/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:55:39 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/24 01:52:07 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_p_1(t_list_env **new_env, char **cmd)
{
	struct stat	filestat;

	stat(cmd[0], &filestat);
	if (!ft_strcmp(cmd[0], "."))
	{
		ft_printf(2, "minishell: .: filename argument required\n"
			".: usage: . filename [arguments]\n");
		return (g_global_exit.exit_status = 2, g_global_exit.exit_status);
	}
	else if (S_ISDIR(filestat.st_mode) && ft_strcmp(cmd[0], ".."))
	{
		ft_printf(2, "minishell : %s: is a directory\n", cmd[0]);
		return (g_global_exit.exit_status = 126, g_global_exit.exit_status);
	}
	else if (!check_slash(cmd[0]))
	{
		if (!access(cmd[0], F_OK) && !access(cmd[0], X_OK))
			execve(cmd[0], cmd, env_arr(new_env));
		else
		{
			ft_printf(2, "minishell : %s: Permission denied\n", cmd[0]);
			return (g_global_exit.exit_status = 126, g_global_exit.exit_status);
		}
	}
	return (0);
}

int	execute_p2(t_list_env **new_env, char **cmd_parsed)
{
	int		i;
	char	**value;
	char	*pathname;

	i = 0;
	value = get_path_value(new_env);
	if (check_value(value, cmd_parsed))
		return (check_value(value, cmd_parsed));
	while (value[i] != NULL)
	{
		pathname = ft_strjoin(value[i], "/");
		pathname = ft_strjoin(pathname, cmd_parsed[0]);
		if (!access(pathname, F_OK) && access(pathname, X_OK))
		{
			ft_printf(2, "minishell : %s: Permission denied\n", pathname);
			g_global_exit.exit_status = 126;
			return (g_global_exit.exit_status);
		}
		else
			execve(pathname, cmd_parsed, env_arr(new_env));
		i++;
	}
	ft_printf(2, "minishell : %s: command not found\n", cmd_parsed[0]);
	g_global_exit.exit_status = 127;
	return (g_global_exit.exit_status);
}

void	execute(t_list_env **new_env, char **cmd_parsed)
{
	int		status;
	int		id;

	if (!cmd_parsed || !cmd_parsed[0])
		return ;
	id = fork();
	if (id == 0)
	{
		rl_catch_signals = 1;
		g_global_exit.killed = 2;
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (execute_p_1(new_env, cmd_parsed))
			exit(g_global_exit.exit_status);
		else if (execute_p2(new_env, cmd_parsed))
			exit(g_global_exit.exit_status);
		exit(g_global_exit.exit_status);
	}
	waitpid(-1, &status, 0);
	exit_status(status);
}
