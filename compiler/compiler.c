/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:21 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/04 21:50:59 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_word(int token)
{
	if ((token == DLR || token == S_QUOTE
		|| token == WORD || token == QST_MARK))
		return (1);
	return (0);
}

int	is_spechar(int token)
{
	if ((token == PIPE || token == RE_APPEND || token == RE_IN
	|| token == RE_OUT || token == HERE_DOC))
		return (1);
	return (0);
}

t_list	*ighnore_space(t_list *head)
{
	t_list	*new_lst;
	t_token	*mytoken;

	new_lst = NULL;
	if (!head)
		return (NULL);
	while (head)
	{
		if (is_word(head->content->token))
		{
			mytoken = new_token(head->content->str, WORD);
			if (!mytoken)
				return (NULL);
			ft_lstadd_back(&new_lst, ft_lstnew(mytoken));
		}
		else if (is_spechar(head->content->token))
		{
			mytoken = new_token(head->content->str, head->content->token);
			if (!mytoken)
				return (NULL);
			ft_lstadd_back(&new_lst, ft_lstnew(mytoken));
		}
		head = head->next;
	}
	return (new_lst);
}

t_list	*compiler(t_list *head)
{
	t_list	*new_lst;
	new_lst = ighnore_space(head);
	if (!new_lst)
		return (NULL);
	if (!check_syntax(new_lst))
		return (free_linked_list(new_lst), NULL);
	return (free_linked_list(new_lst), head);
}
