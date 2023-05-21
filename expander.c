/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:48:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/21 01:34:31 by mouaammo         ###   ########.fr       */
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

t_mylist	*take_env(char **env)
{
	t_env		*myenv;
	t_mylist	*head;
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

void	search_for_key(char *str, t_mylist *myenv, t_list **head)
{
	t_env	*keyval_env;

	while (myenv)
	{
		keyval_env = myenv->content;
		if (ft_strnstr(str, keyval_env->key, ft_strlen(str)))
		{
			(*head)->content->str = keyval_env->value;
		}
		myenv = myenv->next;
	}
}

void	expander(t_list *head, t_mylist *myenv)
{
	while (head)
	{
		if (ft_strchr(head->content->str, '$'))
			if (head->content->token == WORD || head->content->token == QUOTE)
			{
				//search for the string in the linked list
				search_for_key(head->content->str, myenv, &head);
			}
		head = head->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;
	t_mylist	*my_env;

	(void)(ac);
	(void)(av);
	head = NULL;
	str = readline("minishell>> :");
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (0);
	compiler(head);
	head = esc_sp_after_spechar(head);
	my_env = take_env(env);
	expander(head, my_env);
	display(head);
	return (0);
}
