/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:12:11 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/15 18:54:00 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	count_pipes(t_list *head)
{
	int	count;

	count = 1;
	if (!head)
		count = 0;
	while (head)
	{
		if (head->content->token == PIPE)
			count++;
		head = head->next;
	}
	return (count);
}

t_cmds	*bash_parser(t_list *head)
{
	t_cmds	*cmds;
	int		nb_pipes;
	// t_list	*mylist;

	nb_pipes = count_pipes(head);
	if (!nb_pipes)
		return (NULL);
	cmds = malloc(sizeof(t_cmds) * (nb_pipes + 1));
	if (!cmds)
		return (NULL);

	int i = 0;
	while (head)
	{
		cmds[i].commands = NULL;
		while (head && head->content->token != PIPE)
		{
			ft_lstadd_back(&cmds[i].commands, ft_lstnew(head->content));
			head = head->next;
		}
		printf("%s\n", cmds[i++].commands->content->str);
		if (!head)
			break ;
		head = head->next;
	}
	return (NULL);
}

int	main(void)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;

	head = NULL;
	str = readline("minishell>> :");
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (myfree_func(head, trimed_str, str), 1);
	compiler(head);
	bash_parser(head);
	// t_list *varlist;
	// varlist = cmds->commands;
	// int i = 0;
	// while (cmds[i].commands)
	// {
	// 	printf("[%s]\n", cmds[i].commands->content->str);
	// 	// varlist = varlist->next;
	// 	i++;
	// }

	return (myfree_func(head, trimed_str, str));
}
