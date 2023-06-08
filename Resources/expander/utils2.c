/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:32:23 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 02:36:29 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*string_replace(char *phrase, char *oldstring, char *newstring)
{
	int		newlen;
	int		phraselen;
	int		index;
	char	*new_phrase;
	int		total_len;

	if (!oldstring || !newstring)
		return (phrase);
	newlen = ft_strlen(newstring);
	phraselen = ft_strlen(phrase);
	total_len = (phraselen + newlen - ft_strlen(oldstring));
	new_phrase = malloc(sizeof (char) * (total_len + 1));
	if (!new_phrase)
		return (NULL);
	index = ft_str_search_index(phrase, oldstring, ft_strlen(phrase));
	ft_memcpy(new_phrase, phrase, index);
	ft_memcpy(new_phrase + index, newstring, newlen);
	ft_memcpy(new_phrase + index + newlen, phrase + index
		+ ft_strlen(oldstring), phraselen - index - ft_strlen(oldstring));
	new_phrase[total_len] = '\0';
	return (new_phrase);
}

t_list	*esc_sp_after_spechar(t_list *head)
{
	t_list	*newlist;
	t_list	*old_head;

	old_head = head;
	newlist = NULL;
	while (head)
	{
		if (head->content->token == ESP)
		{
			if (head->prev && (is_word(head->prev->content->token)))
			{
				ft_lstadd_back(&newlist, ft_lstnew(new_token(head->content->str,
							head->content->token)));
			}
			head = head->next;
			continue ;
		}
		ft_lstadd_back(&newlist, ft_lstnew(new_token(head->content->str,
					head->content->token)));
		head = head->next;
	}
	return (free_linked_list(old_head), newlist);
}
