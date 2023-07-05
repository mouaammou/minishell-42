/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:12:11 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/04 11:12:46 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*fill_node_with_data(char **my_env)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	if (!node)
		return (NULL);
	node->data.key = ft_strdup(my_env[0]);
	node->data.value = ft_strdup(my_env[1]);
	node->next = NULL;
	return (node);
}

void	update_shelvl(t_list_env *new_env)
{
	int		nb;
	char	*get_value;
	char	*counter;

	nb = 0;
	get_value = get_value_of_key(&new_env, "SHLVL");
	if (get_value != NULL)
	{
		nb = ft_atoi(get_value);
		nb++;
		counter = ft_itoa(nb);
		set_value_of_key(&new_env, "SHLVL", counter);
		free(counter);
	}
	else
		add_back_to_list(&new_env, build_node(ft_strdup("SHLVL"),
				ft_strdup("1")));
}

t_list_env	*env_removed(t_list_env *new_env)
{
	t_list_env	*node;
	t_list_env	*node1;
	t_list_env	*node2;
	t_list_env	*node3;
	char		cwd[1024];

	node = build_node(ft_strdup("PATH"),
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	node1 = build_node(ft_strdup("PWD"),
			ft_strdup(getcwd(cwd, sizeof(cwd))));
	node2 = build_node(ft_strdup("SHLVL"),
			ft_strdup("0"));
	node3 = build_node(ft_strdup("_"),
			ft_strdup("/usr/bin/env"));
	node->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	new_env = node;
	update_shelvl(new_env);
	return (new_env);
}

void	env_removed_bash(t_list_env *new_env, t_list_env *node,
	t_list_env *curr_env, int j)
{
	if (j == 3)
	{
		node = build_node(ft_strdup("PATH"),
				ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
		curr_env->next = node;
	}
	update_shelvl(new_env);
}

t_list_env	*get_env(char **env)
{
	t_list_env	*new_env;
	t_list_env	*curr_env;
	t_list_env	*node;
	char		**my_env;
	int			i;

	i = 0;
	new_env = NULL;
	curr_env = NULL;
	while (env && env[i] != NULL)
	{
		my_env = split_keyvalue(env[i]);
		node = fill_node_with_data(my_env);
		free_args(my_env);
		if (curr_env)
			curr_env->next = node;
		else
			new_env = node;
		curr_env = node;
		i++;
	}
	if (i == 0)
		return (env_removed(new_env));
	env_removed_bash(new_env, node, curr_env, i);
	return (new_env);
}
