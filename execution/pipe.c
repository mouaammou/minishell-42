/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:42:33 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 22:41:59 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commands(char **cmds,
	t_list_env **new_env, t_list_env **m_export)
{
	if (is_builtin(cmds))
		g_global_exit.exit_status = builtin_functions(new_env, m_export, cmds);
	else
		execute(new_env, cmds);
}

void	building_pipes(int i, int *fd, int old_fd_in, int old_fd_out)
{
	int	len;

	len = g_global_exit.len_cmd;
	if (i == 0)
		first_command(fd);
	else if (i < len - 1)
		in_between_commands(fd, old_fd_in, old_fd_out);
	else
		last_command(old_fd_in, old_fd_out);
}

int	execute_cmd(t_list_env **m_export, t_voidlst *commands,
	t_list_env **new_env, t_command	*mycommand)
{
	g_global_exit.exit_status = redirections(commands,
			mycommand->redirections, m_export, new_env);
	return (g_global_exit.exit_status);
}

void	piping(t_list_env **m_export, t_voidlst *commands,
	t_list_env **new_env, int len)
{
	int			i;
	int			id;
	int			fd[2];
	int			old_fd_in;
	int			old_fd_out;

	init_piping(fd, &i);
	while (++i < len)
	{
		old_fd_in = fd[0];
		old_fd_out = fd[1];
		if (i + 1 != len)
			pipe(fd);
		id = fork();
		if (id == 0)
		{	
			building_pipes(i, fd, old_fd_in, old_fd_out);
			exit(execute_cmd(m_export, commands, new_env, commands->content));
		}
		else
			g_global_exit.pid[i] = id;
		close_fds(old_fd_in, old_fd_out, i);
		commands = commands->next;
	}
}

void	ft_pipe(t_list_env **m_export, t_voidlst *commands,
	t_list_env **new_env)
{
	t_command	*mycommand;
	int			len;

	len = list_size(commands);
	g_global_exit.len_cmd = len;
	g_global_exit.size = len;
	if (len == 1)
	{
		mycommand = commands->content;
		redirections(commands, mycommand->redirections, m_export, new_env);
	}
	else if (len > 1)
		piping(m_export, commands, new_env, len);
	waitforchilds();
}
