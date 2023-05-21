/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:17:30 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/20 16:23:47 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	add_back(t_mylist **lst, t_mylist *new)
{
	t_mylist	*head;

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

void	add_front(t_mylist **lst, t_mylist *new)
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

t_mylist	*new_node(void *content)
{
	t_mylist	*node;

	node = NULL;
	node = (t_mylist *) malloc(sizeof(t_mylist));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_mylist	*last_node(t_mylist *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	last_size(t_mylist *lst)
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
