/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:33:24 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/12 17:39:59 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst)
		return ;
	while ((*lst))
	{
		if (del)
			del((*lst)->content);
		temp = *lst;
		(*lst) = (*lst)->next;
		free(temp);
	}
	*lst = NULL;
}
