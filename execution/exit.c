/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:52:10 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/22 22:26:18 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isword(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalpha((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	size_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	ft_exit(char **cmd)
{
	printf("exit\n");
	if (size_cmd(cmd) == 2 && is_all_digits(cmd[1]))
		g_global_exit.exit_status = ft_atoi(cmd[1]);
	else if (size_cmd(cmd) >= 2 && !is_all_digits(cmd[1]))
	{
		g_global_exit.exit_status = 255;
		ft_printf(2, "minishell: exit : %s: numeric" \
		" argument required\n", cmd[1]);
	}
	else if (size_cmd(cmd) > 2 && is_all_digits(cmd[1]))
	{
		g_global_exit.exit_status = 1;
		ft_printf(2, "minishell: exit : too many arguments\n");
	}
	exit(g_global_exit.exit_status);
}
