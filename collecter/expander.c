/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:18:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/29 21:02:20 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	command_expansion(t_voidlst **origin, t_list **head,
	t_voidlst *myenv, int flag)
{
	t_voidlst	*sublst;
	t_token		*mytoken;

	sublst = NULL;
	mytoken = (*head)->content;
	if ((mytoken->token == DLR  || mytoken->token == QUOTE)
		&& (!str_cmp(mytoken->str, "$") || !str_cmp(mytoken->str, "$$")))
		add_back(origin, new_node(mytoken));
	else if ((ft_strchr(mytoken->str, '$') && mytoken->token == QUOTE) || mytoken->token == DLR)
	{
		sublst = expander(*head, myenv);
		if (sublst)
			add_multi_nodes(origin, sublst);
	}
	else
		add_back(origin, new_node(mytoken));
	if (flag)
		(*head) = (*head)->next;
}

void	expand_qts_mark(t_voidlst **origin, t_list **head)
{
	t_voidlst	*sublst;
	t_token		*mytoken;

	sublst = NULL;
	mytoken = (*head)->content;
	free(mytoken->str);
	mytoken->str = ft_itoa(1337);
	if (mytoken->str)
		add_back(origin, new_node(mytoken));
}

t_voidlst	*expander(t_list *head, t_voidlst *myenv)
{
	char		**split;
	char		*searched_str;
	t_voidlst	*sub_lst;
	t_token		*mytoken;

	sub_lst = NULL;
	mytoken = (t_token *)head->content;
	searched_str = search_for_key(mytoken->str, myenv);
	if (searched_str && mytoken->token == DLR)
	{
		split = ft_split(searched_str, ' ');
		sub_lst = new_sublist(split);
	}
	else if (searched_str && mytoken->token == QUOTE)
		sub_lst = new_node(new_token(searched_str, QUOTE));
	// free(searched_str);
	return (sub_lst);
}
