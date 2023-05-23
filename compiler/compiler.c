/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:21 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/23 23:44:38 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_word(int token)
{
	if ((token == QUOTE || token == S_QUOTE || token == DLR
		|| token == WORD) && token != ESP)
		return (1);
	return (0);
}

int	is_spechar(int token)
{
	if ((token == PIPE || token == RE_APPEND || token == RE_IN
	|| token == RE_OUT || token == HERE_DOC) && token != ESP)
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
			ft_lstadd_back(&new_lst, ft_lstnew(mytoken));
		}
		else if (is_spechar(head->content->token))
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
