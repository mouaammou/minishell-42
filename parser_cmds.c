/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:12:11 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/16 17:06:14 by mouaammo         ###   ########.fr       */
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

	nb_pipes = count_pipes(head);
	if (!nb_pipes)
		return (NULL);
	cmds = malloc((nb_pipes + 1) * sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->nb_cmds = nb_pipes;
	int i = 0;
	cmds[i].commands = NULL;
	cmds[i].redirects = NULL;
	while (head)
	{
		while (head && head->content->token != PIPE)// ls -la cat file
		{
			if (head->content->token == WORD || head->content->token == QUOTE || head->content->token == S_QUOTE)
				ft_lstadd_back(&cmds[i].commands, ft_lstnew(head->content));
			else if (head->content->token != WORD && head->content->token != ESP)
				ft_lstadd_back(&cmds[i].redirects, ft_lstnew(head->content));
			head = head->next;
		}
		if (!head)
			break ;
		i++;
		cmds[i].commands = NULL;
		cmds[i].redirects = NULL;
		if (head->content->token == PIPE)
			head = head->next;
	}
	return (cmds);
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
		return (0);
	compiler(head);
	t_cmds *cmds = bash_parser(head);
	t_list *varlist;
	int i = 0;

	while (cmds && i < cmds->nb_cmds)
	{
		varlist = cmds[i].commands;
		printf("command: %d\n", i+1);
		while (varlist)
		{
			printf("[%s]\n", varlist->content->str);
			varlist = varlist->next;
		}
		i++;
	}
	return (0);
}
