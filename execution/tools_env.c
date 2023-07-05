/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:12:46 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/22 00:12:48 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value_of_key(t_list_env **envr, char *key)
{
	t_list_env	*env;
	char		*value;

	env = *envr;
	value = NULL;
	while (env != NULL)
	{
		if (ft_strcmp(env->data.key, key) == 0)
			value = env->data.value;
		env = env->next;
	}
	return (value);
}

t_list_env	*get_node_by_key(t_list_env **envr, char *key)
{
	t_list_env	*env;

	env = *envr;
	while (env != NULL)
	{
		if (ft_strcmp(env->data.key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	set_value_of_key(t_list_env **envr, char *key, char *value)
{
	t_list_env	*env;
	char		*tmp;

	env = *envr;
	while (env != NULL)
	{
		if (ft_strcmp(env->data.key, key) == 0)
		{
			tmp = env->data.value;
			env->data.value = ft_strdup(value);
			free(tmp);
		}
		env = env->next;
	}
}

char	**get_path_value(t_list_env **env)
{
	char	**value;
	char	*res;

	res = NULL;
	value = NULL;
	res = get_value_of_key(env, "PATH");
	if (res != NULL)
	{
		value = ft_split(res, ':');
	}
	return (value);
}

int	env_size(t_list_env *env)
{
	t_list_env	*tmp;
	int			len;

	len = 0;
	tmp = env;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
