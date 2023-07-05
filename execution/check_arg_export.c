/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:43:05 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/23 02:03:17 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_key_export_with_equ(char *cmd1)
{
	int	i;

	i = 0;
	if (cmd1[0] == '_' || ft_isalpha((int)cmd1[0]))
	{
		i = 1;
		while (cmd1[i] != '=' && cmd1[i] != '\0')
		{
			if ((ft_isdigit((int)cmd1[i]) || ft_isalpha((int)cmd1[i])
					|| (cmd1[i + 1] == '=' && cmd1[i] == '+') || cmd1[i] == '_')
				&& cmd1[i] != '\0')
			{
				i++;
			}
			else
				break ;
		}
		if (cmd1[i] == '=')
			return (1);
	}
	return (0);
}

int	key_check_without_equ(char *cmd1)
{
	int	i;

	i = 0;
	if (cmd1[0] == '_' || ft_isalpha((int)cmd1[0]))
	{
		i = 1;
		while (cmd1[i] != '\0')
		{
			if ((ft_isdigit((int)cmd1[i]) || ft_isalpha((int)cmd1[i])
					|| cmd1[i] == '_') && cmd1[i] != '\0')
			{
				i++;
			}
			else
				break ;
		}
		if (cmd1[i] == '\0')
			return (1);
	}
	return (0);
}

int	check_equal_existance(char *cmd1)
{
	int	i;

	i = 0;
	while (cmd1[i] != '\0')
	{
		if (cmd1[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_plus_existance(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	check_p_e_existance(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (1);
		else if (cmd[i] == '=')
			return (0);
		i++;
	}
	return (0);
}
