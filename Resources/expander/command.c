/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:23:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 02:21:32 by mouaammo         ###   ########.fr       */
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
	if (token == RE_APPEND || token == RE_IN
		|| token == RE_OUT || token == HERE_DOC)
		return (1);
	return (0);
}

int	handle_redirection(t_list **newlist,
	t_list **head, t_voidlst *myenv, int mytoken)
{
	char	*join_str;

	join_str = NULL;
	(*head) = (*head)->next;
	while ((*head) && (*head)->content->token != ESP
		&& (*head)->content->token != PIPE
		&& !is_redirect((*head)->content->token))
	{
		join_str = ft_strjoin(join_str,
				ft_strdup(replace_all((*head)->content->str, myenv)));
		(*head) = (*head)->next;
	}
	if (ft_strchr(join_str, ' '))
	{
		printf("❌❌ %s: %s❌\n", join_str, "ambiguous redirect");
		return (0);
	}
	if (join_str)
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
				if (!handle_heredoc(newlist, head, myenv))
					return (0);
			}
			else
			{
				if (!handle_redirection(newlist, head, myenv, mytoken))
					return (0);
			}
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
