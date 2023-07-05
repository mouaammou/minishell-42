/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:30:22 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/19 15:51:49 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal(int status)
{
	if (status == 2)
	{
		ft_printf(1, "\n");
		g_global_exit.exit_status = 130;
	}
	else if (status == 3)
	{
		ft_printf(1, "Quit: 3\n");
		g_global_exit.exit_status = 131;
	}
}

void	exit_status(int status)
{
	int	exit_status;

	exit_status = 0;
	if (g_global_exit.exit > 0)
	{
		if (g_global_exit.exit == 1)
			g_global_exit.exit_status = status / 256;
		g_global_exit.exit++;
		return ;
	}
	if (status == 258)
	{
		g_global_exit.exit_status = 2;
		return ;
	}
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		handle_signal(status);
		return ;
	}
	g_global_exit.exit_status = exit_status;
}
