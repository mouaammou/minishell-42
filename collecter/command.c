/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:23:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/06 02:59:45 by mouaammo         ###   ########.fr       */
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

int	handle_redirection(t_cmds **tmp_list, t_list **head, t_voidlst *myenv, int mytoken)
{
	char *join_str;

	join_str = NULL;
	(*head) = (*head)->next;
	while ((*head) && (*head)->content->token != ESP && !is_redirect((*head)->content->token))
	{
		join_str = ft_strjoin(join_str, replace_all((*head)->content->str, myenv));
		(*head) = (*head)->next;
	}
	if (ft_strchr(join_str, ' '))
	{
		printf("❌❌ %s: %s❌\n", join_str, "ambiguous redirect");
		return (0);
	}
	add_back(&((*tmp_list)->redirects), new_node(new_token(join_str, mytoken)));
	return (1);
}

int	handle_cmd(t_cmds **tmp_list, t_list **head, t_voidlst *myenv)
{
	int		mytoken;

	*tmp_list = node_collecter((t_cmds){NULL, NULL});
	while ((*head) && (*head)->content->token != PIPE)
	{
		mytoken = (*head)->content->token;
		if (mytoken == WORD || mytoken == QUOTE || mytoken == DLR || mytoken == DB_DLR
			|| mytoken == S_QUOTE || mytoken == ESP || mytoken == QST_MARK)
			{
				command_expansion(&((*tmp_list)->commands), head, myenv);
				(*head) = (*head)->next;
			}
		else if (is_redirect(mytoken))
		{
			if (!handle_redirection(tmp_list, head, myenv, mytoken))
				return (0);
		}
	}
	return (1);
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
		if (!handle_cmd(&tmp_list, &tokenizer, myenv))
			return (NULL);
		add_back(&collecter, new_node(tmp_list));
		if (tokenizer && tokenizer->content->token == PIPE)
			tokenizer = tokenizer->next;
	}
	return (collecter);
}
