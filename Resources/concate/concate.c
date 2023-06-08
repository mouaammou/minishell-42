/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:40:37 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 04:45:06 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*concate_strings(t_list **command)
{
	char		*join;

	join = NULL;
	while ((*command) && is_word((*command)->content->token))
	{
		join = ft_strjoin(join, ft_strdup((*command)->content->str));
		(*command) = (*command)->next;
	}
	if (*command && is_redirect((*command)->content->token))
		(*command) = (*command)->prev;
	return (join);
}

int	concate_all(t_token *mytoken, t_list **expander, t_cmds **mynode_cmd)
{
	char	*concate_str;

	if (is_word(mytoken->token) || mytoken->token == ESP)
	{
		concate_str = concate_strings(expander);
		if (concate_str)
		{
			add_back(&((*mynode_cmd)->commands),
				new_node(new_token(concate_str, WORD)));
			free(concate_str);
		}
		else
			add_back(&((*mynode_cmd)->commands),
				new_node(new_token(mytoken->str, mytoken->token)));
		return (1);
	}
	return (0);
}

int	fill_mylist(t_list **expander, t_cmds **mynode_cmd)
{
	t_token		*mytoken;

	*mynode_cmd = node_collecter((t_cmds){NULL, NULL});
	if (!*mynode_cmd)
		return (0);
	while ((*expander) && (*expander)->content->token != PIPE)
	{
		mytoken = (*expander)->content;
		if (!concate_all(mytoken, expander, mynode_cmd))
			add_back(&((*mynode_cmd)->redirects),
				new_node(new_token(mytoken->str, mytoken->token)));
		if ((*expander))
			(*expander) = (*expander)->next;
	}
	return (1);
}

t_voidlst	*bash_concate(t_list *expander)
{
	t_cmds		*mynode_cmd;
	t_voidlst	*parent_list;
	t_list		*tmp;

	mynode_cmd = NULL;
	parent_list = NULL;
	tmp = expander;
	while (expander)
	{
		if (!fill_mylist(&expander, &mynode_cmd))
			return (NULL);
		add_back(&parent_list, new_node(mynode_cmd));
		if (expander && expander->content->token == PIPE)
			expander = expander->next;
	}
	return (free_linked_list(tmp), parent_list);
}
