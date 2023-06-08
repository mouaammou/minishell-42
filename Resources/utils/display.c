/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:13:27 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 20:39:36 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	display(t_voidlst *h_list)
{
	t_cmds		*tmp;
	t_voidlst	*cmds;
	t_token		*token1;
	int			i;

	i = 1;
	while (h_list)
	{
		tmp = h_list->content;
		cmds = tmp->commands;
		printf("command: %d\n", i);
		while (cmds)
		{
			token1 = cmds->content;
			printf("\t[%s]  token: %d\n", token1->str, token1->token);
			cmds = cmds->next;
		}
		printf("\nredirects\n");
		affiche_voidlst(tmp->redirects);
		i++;
		h_list = h_list->next;
	}
}

void	affiche_voidlst(t_voidlst *head)
{
	t_token	*token1;

	while (head)
	{
		token1 = head->content;
		printf("[%s] == token [%d]\n", token1->str, token1->token);
		head = head->next;
	}
	printf("\n");
}

void	display_args(t_voidlst *h_list)
{
	int			i;
	t_command	*tmp;
	char		**cmds;

	i = 1;
	while (h_list)
	{
		tmp = h_list->content;
		cmds = tmp->args;
		printf("command: %d\n", i);
		while (*cmds)
		{
			printf("\t{%s}\n", *cmds);
			cmds++;
		}
		printf("\nredirects\n");
		affiche_voidlst(tmp->redirections);
		i++;
		h_list = h_list->next;
	}
}

void	affiche(t_list *head)
{
	while (head)
	{
		printf("[%s] == token [%d]\n", head->content->str, head->content->token);
		head = head->next;
	}
}
