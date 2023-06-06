/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:18:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/06 00:43:51 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	expande(t_list *head, t_voidlst *myenv, t_voidlst **origin)
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
	else if (mytoken->token == QUOTE || (mytoken->token == DLR && ft_strlen(mytoken->str) == 1))
		add_back(origin, new_node(mytoken));
}

void	command_expansion(t_voidlst **origin, t_list **head, t_voidlst *myenv)
{
	t_token		*mytoken;
	
	mytoken = (*head)->content;
	if ((mytoken->token == DLR || mytoken->token == QUOTE))
		expande(*head, myenv, origin);
	else
		add_back(origin, new_node(mytoken));
}

