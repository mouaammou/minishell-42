/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:23:28 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/20 22:24:41 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_list_env *node)
{
	free(node->data.key);
	free(node->data.value);
	free(node);
}

void	free_env(t_list_env *env)
{
	t_list_env	*tmp;
	t_list_env	*tmp_free;
	int			len;

	tmp = env;
	len = env_size(env);
	if (env == NULL)
		return ;
	while (tmp)
	{
		tmp_free = tmp;
		tmp = tmp->next;
		free_node(tmp_free);
	}
}

void	print_env(t_list_env **envr)
{
	t_list_env	*env;

	env = *envr;
	while (env != NULL)
	{
		printf("%s=%s\n", env->data.key, env->data.value);
		env = env->next;
	}
}

void	print_env_export(t_list_env **envr)
{
	t_list_env	*env;

	env = *envr;
	while (env != NULL)
	{
		if (env->data.value == NULL)
			printf("declare -x %s\n", env->data.key);
		else
			printf("declare -x %s=\"%s\"\n", env->data.key, env->data.value);
		env = env->next;
	}
}
