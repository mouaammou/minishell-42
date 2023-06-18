/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:42:33 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 00:13:35 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commands(char **cmds, t_list_env **new_env, t_list_env **m_export)
{
	if (is_builtin(cmds))
		g_global_exit.exit_status =  builtin_functions(new_env, m_export, cmds);
	else
		execute(new_env, cmds);
	// printf("|%d|\n",g_global_exit.exit_status);
}

void first_command(int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2 failed");
	close(fd[1]);
}

void	in_between_commands(int *fd, int old_fd_in, int old_fd_out)
{
	close(fd[0]);
	close(old_fd_out);
	if (dup2(old_fd_in, STDIN_FILENO) == -1)
		perror("dup2 failed");
	close(old_fd_in);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2 failed");
	close(fd[1]);
}

void last_command(int old_fd_in, int old_fd_out)
{
	close(old_fd_out);
	if (dup2(old_fd_in, STDIN_FILENO) == -1)
		perror("dup2 failed");
	close(old_fd_in);	
}

void	ft_pipe(t_list_env **m_export, t_voidlst *commands, t_list_env **new_env)
{
	t_command	*mycommand;
	int fd[2];
	int len;
	int sig;
	int i;
	int old_fd_in, old_fd_out;
	int j = 0;
	// old_fd_in = -1;
	// old_fd_out = -1;
	fd[0] = -1;
	fd[1] = -1;
	len = list_size(commands);
	g_global_exit.size = len;
	if (len == 1)
	{
		mycommand = commands->content;
		redirections(commands, mycommand->redirections, m_export, new_env);
	}
	else if (len > 1)
	{
		i = -1;
		while (++i < len)
		{
			mycommand = commands->content;
			old_fd_in = fd[0];
			old_fd_out = fd[1];
			if (i + 1 != len)
				pipe(fd);
			int id = fork();
			if (id == 0)
			{	
				if (i == 0)
					first_command(fd);
				else if (i < len - 1)
					in_between_commands(fd, old_fd_in, old_fd_out);
				else
					last_command(old_fd_in, old_fd_out);
				g_global_exit.exit_status = redirections(commands, mycommand->redirections, m_export, new_env);
				exit(g_global_exit.exit_status);
			}
			else
				g_global_exit.pid[j++] = id;
			g_global_exit.len = j;
			close(old_fd_in);
			close(old_fd_out);
			commands = commands->next;
		}
	}
	int	k;

	k = 0;
	while (waitpid(g_global_exit.pid[k++], &g_global_exit.exit_status, 0) != -1)
		;
	if (WIFEXITED(g_global_exit.exit_status))
		WEXITSTATUS(g_global_exit.exit_status);
	g_global_exit.exit_status = g_global_exit.exit_status % 255;
}
