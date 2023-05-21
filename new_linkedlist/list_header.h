/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:17:16 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/20 16:19:11 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct list
{
	void			*content;
	struct list		*next;
	struct list		*prev;
}	t_mylist;

void		add_back(t_mylist **lst, t_mylist *new);
void		add_front(t_mylist **lst, t_mylist *new);
t_mylist	*new_node(void *content);
t_mylist	*last_node(t_mylist *lst);
int			last_size(t_mylist *lst);

#endif
