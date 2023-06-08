/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:17:30 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/06 03:37:57 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	add_back(t_voidlst **lst, t_voidlst *new)
{
	t_voidlst	*head;

	if (!lst || !new)
		return ;
	head = *lst;
	if (*lst)
	{
		head = last_node(head);
		new->next = NULL;
		new->prev = head;
		head->next = new;
	}
	else
		*lst = new;
}

void	add_front(t_voidlst **lst, t_voidlst *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
		new->next = *lst;
		new->prev = NULL;
		(*lst)->prev = new;
	}
	*lst = new;
}

t_voidlst	*new_node(void *content)
{
	t_voidlst	*node;

	node = NULL;
	node = (t_voidlst *) malloc(sizeof(t_voidlst));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_voidlst	*last_node(t_voidlst *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	list_size(t_voidlst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
