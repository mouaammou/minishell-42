/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:50:13 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/05 01:36:03 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LST_H
# define LINKED_LST_H

typedef enum tokens
{
	WHATEVER = 0,
	QUOTE = 1,
	S_QUOTE = 2,
	WORD = 3,
	PIPE = 4,
	RE_OUT = 5,
	RE_IN = 6,
	RE_APPEND = 7,
	HERE_DOC = 8,
	ESP = 9,
	DLR = 10,
	DB_DLR = 11,
	QST_MARK = 12
}	t_etoken;

typedef struct token
{
	char		*str;
	t_etoken	token;
}t_token;

typedef struct s_list
{
	t_token			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list	*ft_lstnew(t_token *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
