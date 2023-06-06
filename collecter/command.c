/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:23:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/06 17:29:25 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	add_multi_nodes(t_list **origin, t_voidlst *newlist)
{
	while (newlist)
	{
		ft_lstadd_back(origin, ft_lstnew(newlist->content));
		newlist = newlist->next;
	}
}

int	is_redirect(int token)
{
	if (token == RE_APPEND || token == RE_IN || token == RE_OUT || token == HERE_DOC)
		return (1);
	return (0);
}

int	handle_redirection(t_list **newlist, t_list **head, t_voidlst *myenv, int mytoken)
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
	ft_lstadd_back(newlist, ft_lstnew(new_token(join_str, mytoken)));
	return (1);
}

int	handle_cmd(t_list **newlist, t_list **head, t_voidlst *myenv)
{
	int		mytoken;

	while ((*head))
	{
		mytoken = (*head)->content->token;
		if (is_redirect(mytoken))
		{
			if (mytoken == HERE_DOC)
			{
				// (*head) = (*head)->next;
				handle_heredoc(head, myenv);
				(*head) = (*head)->next;
			}
			else 
			if (!handle_redirection(newlist, head, myenv, mytoken))
				return (0);
		}
		else
		{
			command_expansion(newlist, head, myenv);
			(*head) = (*head)->next;
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

t_list	*bash_collecter(t_list *tokenizer, t_voidlst *myenv)
{
	t_list		*new_list;
	t_list		*tmphead;

	tmphead = tokenizer;
	new_list = NULL;
	while (tokenizer)
	{
		if (!handle_cmd(&new_list, &tokenizer, myenv))
			return (NULL);
	}
	return (free_linked_list(tmphead), new_list);
}
