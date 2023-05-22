/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:48:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/22 22:28:00 by mouaammo         ###   ########.fr       */
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
		if (ft_strnstr(str, keyval_env->key, ft_strlen(str)))
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

t_voidlst	*new_sublist(char **split)
{
	t_voidlst	*head;
	int			i;
	t_token		*mytoken;

	i = 0;
	head = NULL;
	while (split && split[i])
	{
		mytoken = malloc(sizeof (t_token));
		if (!mytoken)
		{
			perror("");
			exit (0);
		}
		mytoken->token = WORD;
		mytoken->str = split[i];
		add_back(&head, new_node(mytoken));
		i++;
	}
	return (head);
}

t_voidlst	*expander(t_list *head, t_voidlst *myenv)
{
	char		**split;
	int			size;
	char		*searched_str;
	t_voidlst	*sub_lst;
	t_token		*mytoken;

	sub_lst = NULL;
	mytoken = NULL;
	searched_str = search_for_key(head->content->str, myenv);
	if (searched_str && head->content->token == WORD)
	{
		split = ft_split(searched_str, ' ');
		size = count_size(split);
		sub_lst = new_sublist (split);
	}
	else if (searched_str && head->content->token == QUOTE)
	{
		mytoken = malloc(sizeof (t_token));
		if (!mytoken)
		{
			perror("");
			exit (0);
		}
		mytoken->token = QUOTE;
		mytoken->str = searched_str;
		sub_lst = new_node (mytoken);
	}
	return (sub_lst);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_list	*head;
// 	char	*str;
// 	char	*trimed_str;
// 	t_voidlst	*my_env;

// 	(void)(ac);
// 	(void)(av);
// 	head = NULL;
// 	str = readline("minishell>> :");
// 	if (!str)
// 		return (0);
// 	trimed_str = ft_strtrim(str, " ");
// 	if (!give_tokens(&head, trimed_str))
// 		return (0);
// 	compiler(head);
// 	head = esc_sp_after_spechar(head);
// 	my_env = take_env(env);
// 	// expander(head, my_env);
// 	bash_collecter(head);
// 	// display_args(cmds);
// 	printf("====\n");
// 	// display_redires(cmds);
// 	// display(head);
// 	return (0);
// }
