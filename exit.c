/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:52:10 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/08 01:46:04 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isWord(char *str)
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

// 1 : ./mi exit => ac = 2 + !av[2]
// 2 : ./mi exit 20 => ac = 3 + av[2] is digit
// 3 : ./mi exit fh iey dhg => ac > 3 + av[2] is alpha
// 4 : ./mi exit 20 iey dhg => ac > 3 + av[2] is digit
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
	//exit ma7daha walo => il affiche exit + g_exit = 0
	// exit 7daha bzzf args  + lowl machi nbr => too many arguments + g_exit = 1
	// exit 7daha bzzf args  + lowl machi nbr => numeric argument required + g_exit = 255
	// exit 7daha 7aja wa7da => atoi % 256
	// printf("size = %d\n", size_cmd(cmd));
	printf("exit\n");
	if (size_cmd(cmd) == 2 && is_all_digits(cmd[1]))
		global_exit.exit_status = ft_atoi(cmd[1]) % 256;
	else if (size_cmd(cmd) >= 2 && isWord(cmd[1]))
	{
		global_exit.exit_status = 255;
		printf("minishell: exit : %s: numeric argument required\n", cmd[1]);
	}
	else if (size_cmd(cmd) > 2 && is_all_digits(cmd[1]))
	{
		global_exit.exit_status = 1;
		printf("minishell: exit : too many arguments\n");
	}
	exit(global_exit.exit_status);
}