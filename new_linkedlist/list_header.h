/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:17:16 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/21 14:17:05 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct list
{
	void			*content;
	struct list		*next;
	struct list		*prev;
}	t_voidlst;

void		add_back(t_voidlst **lst, t_voidlst *new);
void		add_front(t_voidlst **lst, t_voidlst *new);
t_voidlst	*new_node(void *content);
t_voidlst	*last_node(t_voidlst *lst);
int			last_size(t_voidlst *lst);

#endif
