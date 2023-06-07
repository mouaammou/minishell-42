/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:59:46 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/07 02:55:57 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	*msg_error(char *str)
{
	printf("ERR: %s\n", str);
	return (0);
}

int	myfree_func(t_list *head, char *trimed_str, char *str)
{
	free(trimed_str);
	free_linked_list(head);
	free(str);
	return (0);
}

void	free_linked_list(t_list *head)
{
	t_list	*tmp;
	t_token	*mytoken;

	while (head)
	{
		mytoken = head->content;
		tmp = head->next;
		free(mytoken->str);
		free(mytoken);
		free(head);
		head = tmp;
	}
}

void	free_nodes(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
