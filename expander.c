/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:48:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/23 22:46:39 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*split_key_value(char *env)
{
	char	**split;
	t_env	*key_value;

	split = ft_split(env, '=');
	key_value = malloc (sizeof (t_env));
	if (!key_value)
	{
		perror("");
		exit (EXIT_FAILURE);
	}
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
		if (str_cmp(str + 1, keyval_env->key) == 0)
		{
			return (keyval_env->value);
		}
		myenv = myenv->next;
	}
	return (NULL);
}

int	count_size(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

void	ft_error(char *error, int error_val)
{
	ft_putstr_fd(error, 1);
	exit (error_val);
}

t_token	*new_token(char *str, int token)
{
	t_token	*mytoken;

	mytoken = malloc(sizeof (t_token));
	if (!mytoken)
		ft_error("malloc failed\n", 1);
	mytoken->str = str;
	mytoken->token = token;
	return (mytoken);
}

t_voidlst	*new_sublist(char **split)
{
	t_voidlst	*head;
	int			i;

	i = 0;
	head = NULL;
	while (split && split[i])
	{
		add_back(&head, new_node(new_token(split[i], WORD)));
		if (split[i + 1])
			add_back(&head, new_node(new_token(ft_strdup(" "), ESP)));
		i++;
	}
	return (head);
}

int	index_of_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/***** new algorith
 * 1- token everything include dollar
 * 2- check grammar
 * 3- expande the variables
 * 4- concate no white space
*/

t_voidlst	*expander(t_list *head, t_voidlst *myenv)
{
	char		**split;
	int			size;
	char		*searched_str;
	t_voidlst	*sub_lst;
	int			index;

	sub_lst = NULL;
	index = index_of_char(head->content->str, '$');
	searched_str = search_for_key(head->content->str + index, myenv);
	if (searched_str && head->content->token == WORD)
	{
		split = ft_split(searched_str, ' ');
		size = count_size(split);
		sub_lst = new_sublist(split);
	}
	else if (searched_str && head->content->token == QUOTE)
		sub_lst = new_node(new_token(searched_str, QUOTE));
	return (sub_lst);
}

