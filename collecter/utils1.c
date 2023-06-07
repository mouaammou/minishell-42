/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:20:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/07 22:35:11 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_env	*split_key_value(char *env)
{
	char	**split;
	t_env	*key_value;

	key_value = malloc (sizeof (t_env));
	if (!key_value)
		return (NULL);
	split = ft_split(env, '=');
	key_value->key = ft_strdup(split[0]);
	key_value->value = ft_substr(env, ft_strlen(split[0]) + 1, ft_strlen(env));
	free_all(split);
	return (key_value);
}

void	free_all(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

t_voidlst	*take_env(char **env)
{
	t_env		*myenv;
	t_voidlst	*head;
	int			i;

	head = NULL;
	i = 0;
	while (env && env[i])
	{
		myenv = split_key_value(env[i]);
		add_back(&head, new_node(myenv));
		i++;
	}
	return (head);
}

char	*search_for_key(char *str, t_voidlst *myenv)
{
	t_env	*keyval_env;

	while (myenv)
	{
		keyval_env = myenv->content;
		if (str_cmp(str, keyval_env->key) == 0)
			return (keyval_env->value);
		myenv = myenv->next;
	}
	return (NULL);
}

void	ft_error(char *error, int error_val)
{
	ft_putstr_fd(error, 1);
	exit (error_val);
}
