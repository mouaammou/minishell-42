/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:26:49 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/01 05:36:00 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list_env **env, t_list_env **export_list, char **cmd)
{
	if (!cmd[1])
	{
		sort_list(*export_list);
		print_env_export(export_list);
		return (0);
	}
	else if (check_key_value_isvalid_export(cmd[1]))
	{
		export_valid(env, export_list, cmd[1]);
		return (0);
	}
	else
	{
		ft_printf("export: `%s': not a valid identifier\n", cmd[1]);
		return (1);
	}
	return (1);
}
