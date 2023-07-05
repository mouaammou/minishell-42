/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:46:18 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 22:47:21 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_glob(t_exit *glob)
{
	int	i;

	i = -1;
	glob->heredoc = 0;
	glob->killed = 0;
	glob->gnl = 0;
	glob->exit_status = 0;
	glob->exit = 0;
	glob->flag = 1;
	while (++i < 1024)
		glob->pid[i] = 0;
}

void	prompt(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_interrupt(int sig)
{
	t_exit	*glob;

	glob = &g_global_exit;
	if (sig == SIGINT)
	{
		if (ft_kill(glob))
			glob->exit_status = 130;
		else
			glob->exit_status = 1;
		if (g_global_exit.heredoc)
		{
			g_global_exit.flag = 0;
			glob->exit_status = 1;
			close(0);
			g_global_exit.heredoc = 0;
		}
		else
			prompt();
		glob->killed = 0;
	}
	else if (sig == SIGQUIT)
		glob->exit_status = 0;
}

void	handler(int sig)
{
	t_exit	*glob;

	glob = &g_global_exit;
	if (sig == SIGUSR1)
	{
		glob->exit = 1;
	}
}

int	ft_kill(t_exit *glob)
{
	int	i;

	i = 0;
	while (i < glob->len)
	{
		glob->killed = 1;
		kill(glob->pid[i], SIGKILL);
		i++;
	}
	glob->len = 0;
	if (i > 0)
		return (1);
	return (0);
}
