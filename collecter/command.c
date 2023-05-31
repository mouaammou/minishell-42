/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:23:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/31 21:02:22 by mouaammo         ###   ########.fr       */
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

int	is_redirect(int token)
{
	if (token == RE_APPEND || token == RE_IN || token == RE_OUT || token == HERE_DOC)
		return (1);
	return (0);
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
				command_expansion(&((*tmp_list)->commands), head, myenv, 0);
		else if (is_redirect((*head)->content->token))
		{
			if ((*head)->next && ((*head) = (*head)->next))
				command_expansion(&((*tmp_list)->redirects), head, myenv, 1);
		}
		if (*head)
			(*head) = (*head)->next;
	}
}

t_cmds	*node_collecter(t_cmds args)
{
	t_cmds	*new_collecter;

	new_collecter = malloc (sizeof (t_cmds));
	if (!new_collecter)
		return (NULL);
	new_collecter->commands = args.commands;
	new_collecter->redirects = args.redirects;
	return (new_collecter);
}

t_voidlst	*bash_collecter(t_list *tokenizer, t_voidlst *myenv)
{
	t_voidlst	*collecter;
	t_cmds		*tmp_list;
	t_list		*tmphead;

	collecter = NULL;
	tmp_list = NULL;
	tmphead = tokenizer;
	while (tokenizer)
	{
		handle_cmd(&tmp_list, &tokenizer, myenv);
		add_back(&collecter, new_node(tmp_list));
		if (tokenizer && tokenizer->content->token == PIPE)
			tokenizer = tokenizer->next;
	}
	return (free_nodes(tmphead), collecter);
}
