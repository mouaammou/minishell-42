/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_cases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:12:27 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/05 14:01:49 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_export_env(t_list_env **env,
	t_list_env **export_list, char **key_value)
{
	t_list_env	*new1;
	t_list_env	*new2;
	t_env		content;
	t_env		content_;

	content.key = ft_strdup(key_value[0]);
	content.value = ft_strdup(key_value[1]);
	content_.key = ft_strdup(key_value[0]);
	content_.value = ft_strdup(key_value[1]);
	new1 = ft_lstnew_node(content);
	add_back_to_list(env, new1);
	new2 = ft_lstnew_node(content_);
	add_back_to_list(export_list, new2);
}

void	add_to_export_only(t_list_env **export_list, char *cmd)
{
	t_list_env	*new;
	t_env		content;

	content.key = ft_strdup(cmd);
	content.value = NULL;
	new = ft_lstnew_node(content);
	add_back_to_list(export_list, new);
}

void	add_to_env(t_list_env **env, char *key, char *value)
{
	t_list_env	*new;
	t_env		content;

	content.key = key;
	content.value = value;
	new = ft_lstnew_node(content);
	add_back_to_list(env, new);
}

void	export_equ_only(t_list_env **env, t_list_env **export_list, char *cmd)
{
	char		**key_value;

	key_value = key_value_of_arg(cmd);
	if (get_node_by_key(export_list, key_value[0]) != NULL)
	{
		if (key_value[1] == NULL)
			key_value[1] = ft_strdup("");
		set_value_of_key(export_list, key_value[0], key_value[1]);
		if (get_node_by_key(env, key_value[0]) == NULL)
			add_to_env(env, ft_strdup(key_value[0]), ft_strdup(key_value[1]));
		else
			set_value_of_key(env, key_value[0], key_value[1]);
	}
	else
	{
		if (key_value[1] == NULL)
			key_value[1] = ft_strdup("");
		add_to_export_env(env, export_list, key_value);
	}
	free(key_value[0]);
	if (key_value[1] != NULL)
		free(key_value[1]);
	free(key_value);
}

void	export_join(t_list_env **env, t_list_env **export_list, char *cmd)
{
	char	**key_value;
	char	*new_value;
	char	*tmp;

	key_value = key_value_of_arg(cmd);
	if (get_node_by_key(export_list, key_value[0]) != NULL)
	{
		if (key_value[1] == NULL)
			return ;
		else
		{
			tmp = get_value_of_key(export_list,
						key_value[0]);
			new_value = ft_strjoin_export(tmp, key_value[1]);
			set_value_of_key(export_list, key_value[0], new_value);
			if (get_node_by_key(env, key_value[0]) == NULL)
				add_to_env(env, ft_strdup(key_value[0]), ft_strdup(new_value));
			else
				set_value_of_key(env, key_value[0], new_value);
			free(new_value);
		}
	}
	else
	{
		if (key_value[1] == NULL)
			key_value[1] = ft_strdup("");
		add_to_export_env(env, export_list, key_value);
	}
	free(key_value[0]);
	if (key_value[1] != NULL)
		free(key_value[1]);
	free(key_value);
}
