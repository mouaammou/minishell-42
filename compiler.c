/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:21 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/17 22:39:09 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_list	*ighnore_space(t_list *head)
{
	t_list	*new_lst;

	new_lst = NULL;
	if (!head)
		return (NULL);
	while (head)
	{
		if (head->content->token != ESP)
			ft_lstadd_back(&new_lst, ft_lstnew(head->content));
		head = head->next;
	}
	return (new_lst);
}

void	compiler(t_list *head)
{
	t_list	*new_lst;

	new_lst = ighnore_space(head);
	check_syntax(new_lst);
	free_nodes(new_lst);
}
