/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_double_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 04:27:25 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 04:41:41 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_command	*allocate_and_fill(t_voidlst	*cmds)
{
	t_command	*mycommand;
	int			size;
	t_token		*mytoken;
	int			i;

	mycommand = malloc (sizeof (t_command));
	if (!mycommand)
		return (NULL);
	size = list_size(cmds);
	mycommand->args = malloc (sizeof (char *) * (size + 1));
	if (!mycommand->args)
		return (NULL);
	i = 0;
	while (cmds)
	{
		mytoken = cmds->content;
		if (mytoken && mytoken->token != ESP)
			mycommand->args[i++] = ft_strdup(mytoken->str);
		cmds = cmds->next;
	}
	mycommand->args[i] = NULL;
	return (mycommand);
}

int	fill_command(t_voidlst *cmds, t_voidlst *redirs, t_voidlst **new_list)
{
	t_command	*mycommand;
	t_token		*mytoken;

	mycommand = allocate_and_fill(cmds);
	if (!mycommand)
		return (0);
	mycommand->redirections = NULL;
	while (redirs)
	{
		mytoken = redirs->content;
		add_back(&mycommand->redirections,
			new_node(new_token(mytoken->str, mytoken->token)));
		redirs = redirs->next;
	}
	add_back(new_list, new_node(mycommand));
	return (1);
}

t_voidlst	*parse_to_args(t_voidlst *h_list)
{
	t_cmds		*tmp;
	t_voidlst	*new_list;
	t_voidlst	*temp_list;

	new_list = NULL;
	temp_list = h_list;
	while (h_list)
	{
		tmp = h_list->content;
		if (!fill_command(tmp->commands, tmp->redirects, &new_list))
			return (0);
		h_list = h_list->next;
	}
	return (free_big_list(temp_list), new_list);
}
