/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:48:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/24 15:09:30 by mouaammo         ###   ########.fr       */
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
	return (-1);
}

/***** new algorith
 * 1- token everything include dollar
 * 2- check grammar
 * 3- expande the variables
 * 4- concate no white space
*/

//what searched str will append
char	*what_str_take(t_token *mytoken, char **searched_str, t_voidlst *myenv)
{
	char		*rightstr;
	int			index;

	rightstr = NULL;
	*searched_str = NULL;
	index = 0;
	if (mytoken->token == QUOTE)
	{
		
		index = index_of_char(mytoken->str, '$');
		*searched_str = search_for_key(mytoken->str + index, myenv);
	}
	else
		*searched_str = search_for_key(mytoken->str, myenv);
	if (index > 0)
		rightstr = ft_substr(mytoken->str, 0, ft_strlen(mytoken->str) - ft_strlen(mytoken->str + index));
	return (rightstr);
}

t_voidlst	*expander(t_list *head, t_voidlst *myenv)
{
	char		**split;
	char		*searched_str;
	t_voidlst	*sub_lst;
	t_token		*mytoken;
	char		*rightstr;

	sub_lst = NULL;
	mytoken = (t_token *)head->content;
	// printf("{%s} --\n", mytoken->str);
	// exit (0);
	rightstr = what_str_take(mytoken, &searched_str, myenv);
	if (searched_str && mytoken->token == DLR)
	{
		split = ft_split(searched_str, ' ');
		sub_lst = new_sublist(split);
	}
	else if (searched_str && mytoken->token == QUOTE)
	{
		if (rightstr)
			searched_str = ft_strjoin(rightstr, searched_str);
		sub_lst = new_node(new_token(searched_str, QUOTE));
	}
	return (sub_lst);
}

