/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_cases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:37:16 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/11 14:35:55 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_export_env(t_list_env **env,
	t_list_env **export_list, char **key_value)
{
	t_list_env	*new1;
	t_list_env	*new2;
	t_env		content;

	content.key = key_value[0];
	content.value = key_value[1];
	new1 = ft_lstnew_node(content);
	add_back_to_list(env, new1);
	new2 = ft_lstnew_node(content);
	add_back_to_list(export_list, new2);
}

void	add_to_export_only(t_list_env **export_list, char *cmd)
{
	t_list_env	*new;
	t_env		content;

	content.key = cmd;
	content.value = NULL;
	new = ft_lstnew_node(content);
	add_back_to_list(export_list, new);
}

void	export_equ_only(t_list_env **env, t_list_env **export_list, char *cmd)
{
	char		**key_value;

	key_value = key_value_of_arg(cmd);
	if (get_node_by_key(export_list, key_value[0]) != NULL)
	{
		if (key_value[1] == NULL)
			key_value[1] = ft_strdup("");
		set_value_of_key(env, key_value[0], key_value[1]);
		set_value_of_key(export_list, key_value[0], key_value[1]);
	}
	else
	{
		add_to_export_env(env, export_list, key_value);
	}
}

void	export_join(t_list_env **env, t_list_env **export_list, char *cmd)
{
	char	**key_value;
	char	*new_value;

	key_value = key_value_of_arg(cmd);
	if (get_node_by_key(export_list, key_value[0]) != NULL)
	{
		if (key_value[1] == NULL)
			return ;
		else
		{
			new_value = ft_strjoin_export(get_value_of_key(export_list,
						key_value[0]), key_value[1]);
			set_value_of_key(env, key_value[0], new_value);
			set_value_of_key(export_list, key_value[0], new_value);
		}
	}
	else
	{
		add_to_export_env(env, export_list, key_value);
	}
}
