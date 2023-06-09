/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:18:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/09 23:20:42 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_list	*bash_expander(t_list *tokenizer, t_voidlst *myenv)
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

void	expande(t_list *head, t_voidlst *myenv, t_list **origin)
{
	t_token		*mytoken;
	char		*string_value;
	char		**split;
	t_voidlst	*sub_lst;

	mytoken = (head)->content;
	string_value = search_and_replace(&mytoken, myenv);
	if (string_value && mytoken->token == DLR && ft_strlen(mytoken->str) > 1)
	{
		split = ft_split(mytoken->str, ' ');
		sub_lst = new_sublist(split, mytoken->token);
		if (sub_lst)
			add_multi_nodes(origin, sub_lst);
	}
	else if (mytoken->token == QUOTE || (mytoken->token == DLR
			&& ft_strlen(mytoken->str) == 1))
		ft_lstadd_back(origin, ft_lstnew(new_token(mytoken->str,
					mytoken->token)));
}

void	command_expansion(t_list **origin, t_list **head, t_voidlst *myenv)
{
	t_token	*mytoken;

	mytoken = (*head)->content;
	if ((mytoken->token == DLR || mytoken->token == QUOTE))
		expande(*head, myenv, origin);
	else if (mytoken->token == QST_MARK)
		ft_lstadd_back(origin, ft_lstnew(new_token(ft_itoa(g_exit_status),
					mytoken->token)));
	else
		ft_lstadd_back(origin, ft_lstnew(new_token(mytoken->str,
					mytoken->token)));
}
