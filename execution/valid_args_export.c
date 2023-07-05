/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:05:15 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/23 02:04:11 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_valid(t_list_env **env, t_list_env **export_list, char *cmd)
{
	if (check_equal_existance(cmd) && !check_plus_existance(cmd))
	{
		export_equ_only(env, export_list, cmd);
	}
	else if (check_equal_existance(cmd) && check_plus_existance(cmd))
		export_join(env, export_list, cmd);
	else
	{
		if (get_node_by_key(export_list, cmd) != NULL)
		{
			return ;
		}
		else
		{
			add_to_export_only(export_list, cmd);
		}
	}
}

int	check_key_value_isvalid_export(char *cmd)
{
	int	i;

	i = 0;
	if (check_equal_existance(cmd))
	{
		if (!check_key_export_with_equ(cmd))
			return (0);
	}
	else
	{
		if (!key_check_without_equ(cmd))
			return (0);
	}
	return (1);
}

char	**split_keyvalue(char *env)
{
	char	**split;
	char	**key_value;

	key_value = malloc (3 * sizeof(char *));
	if (!key_value)
		return (NULL);
	split = ft_split(env, '=');
	key_value[0] = ft_strdup(split[0]);
	key_value[1] = ft_substr(env, ft_strlen(split[0]) + 1, ft_strlen(env));
	key_value[2] = NULL;
	free_args(split);
	return (key_value);
}
