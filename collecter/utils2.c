/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:21:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/06 16:55:00 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_token	*new_token(char *str, int token)
{
	t_token	*mytoken;

	mytoken = malloc(sizeof (t_token));
	if (!mytoken)
		return (NULL);
	mytoken->str =  ft_strdup(str);
	mytoken->token = token;
	return (mytoken);
}

t_voidlst	*new_sublist(char **split, int token)
{
	t_voidlst	*head;
	int			i;

	i = 0;
	head = NULL;
	while (split && split[i])
	{
		add_back(&head, new_node(new_token(ft_strdup(split[i]), token)));
		if (split[i + 1])
			add_back(&head, new_node(new_token(ft_strdup(" "), token)));
		i++;
	}
	free_all(split);
	return (head);
}

int	index_of_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	str_cmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

t_list	*esc_sp_after_spechar(t_list *head)
{
	t_list	*newlist;
	int		token;
	t_list	*old_head;

	old_head  = head;
	newlist = NULL;
	while (head)
	{
		if (head->content->token == ESP)
		{
			token = head->prev->content->token;
			if (head->prev && (token == WORD || token == QUOTE
					|| token == S_QUOTE || token == DLR))
			{
				ft_lstadd_back(&newlist, ft_lstnew(new_token(head->content->str, head->content->token)));
			}
			head = head->next;
			continue ;
		}
		ft_lstadd_back(&newlist, ft_lstnew(new_token(head->content->str, head->content->token)));
		head = head->next;
	}
	return (free_linked_list(old_head), newlist);
}
