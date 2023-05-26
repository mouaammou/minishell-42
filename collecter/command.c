/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:23:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/26 18:43:08 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	add_multi_nodes(t_voidlst **origin, t_voidlst *newlist)
{
	while (newlist)
	{
		add_back(origin, new_node(newlist->content));
		newlist = newlist->next;
	}
}

void	handle_cmd(t_cmds **tmp_list, t_list **head, t_voidlst *myenv)
{
	int	mytoken;

	*tmp_list = node_collecter((t_cmds){NULL, NULL});
	while ((*head) && (*head)->content->token != PIPE)
	{
		mytoken = (*head)->content->token;
		if (mytoken == WORD || mytoken == QUOTE || mytoken == DLR
			|| mytoken == S_QUOTE || mytoken == ESP || mytoken == QST_MARK)
		{
			if (mytoken == QST_MARK)
				expand_qts_mark(&((*tmp_list)->commands), head);
			else
				command_expansion(&((*tmp_list)->commands), head, myenv, 0);
		}
		else
			command_expansion(&((*tmp_list)->redirects), &(*head)->next,
				myenv, 1);
		(*head) = (*head)->next;
	}
}

t_cmds	*node_collecter(t_cmds args)
{
	t_cmds	*new_collecter;

	new_collecter = malloc (sizeof (t_cmds));
	if (!new_collecter)
		ft_error("malloc failed\n", 3);
	new_collecter->commands = args.commands;
	new_collecter->redirects = args.redirects;
	return (new_collecter);
}

t_voidlst	*bash_collecter(t_list *tokenizer, t_voidlst *myenv)
{
	t_voidlst	*collecter;
	t_cmds		*tmp_list;

	collecter = NULL;
	tmp_list = NULL;
	while (tokenizer)
	{
		handle_cmd(&tmp_list, &tokenizer, myenv);
		add_back(&collecter, new_node(tmp_list));
		if (tokenizer && tokenizer->content->token == PIPE)
			tokenizer = tokenizer->next;
	}
	return (collecter);
}
