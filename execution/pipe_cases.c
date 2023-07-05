/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:34:32 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 22:36:00 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_command(int *fd)
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

void	last_command(int old_fd_in, int old_fd_out)
{
	close(old_fd_out);
	if (dup2(old_fd_in, STDIN_FILENO) == -1)
		perror("dup2 failed");
	close(old_fd_in);
}

void	close_fds(int old_fd_in, int old_fd_out, int i)
{
	g_global_exit.len = i;
	close(old_fd_in);
	close(old_fd_out);
}

void	init_piping(int *fd, int *i)
{
	fd[0] = -1;
	fd[1] = -1;
	*i = -1;
}
