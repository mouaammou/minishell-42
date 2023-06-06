/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_db_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/05 22:39:11 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_list	*token_dbquotes(t_list *tokenizer)
{
	t_list	*new_list;
	t_list	*old_tokenizer;

	old_tokenizer = tokenizer;
	new_list = NULL;
	while (tokenizer)
	{
		if (ft_strchr(tokenizer->content->str, '\"'))
		{
			// if (tokenizer->content->token == QUOTE)
			// 	give_tokens(&new_list, tokenizer->content->str, 1);
			// else
				give_tokens(&new_list, tokenizer->content->str);
		}
		else
			ft_lstadd_back(&new_list, ft_lstnew(new_token(tokenizer->content->str, tokenizer->content->token)));;
		tokenizer = tokenizer->next;
	}
	return (new_list);
}

// t_list	*token_the_string(char *str)
// {
// 	t_list	*new_list;
// 	t_list	*old_tokenizer;

// 	new_list = NULL;
// 	while (tokenizer)
// 	{
// 		if (tokenizer->content->token == QUOTE || tokenizer->content->token == DLR)
// 		{
// 			if (tokenizer->content->token == QUOTE)
// 				give_tokens(&new_list, tokenizer->content->str, 1);
// 			else
// 				give_tokens(&new_list, tokenizer->content->str, 0);
// 		}
// 		else
// 			ft_lstadd_back(&new_list, ft_lstnew(new_token(tokenizer->content->str, tokenizer->content->token)));;
// 		tokenizer = tokenizer->next;
// 	}
// 	return (new_list);
// }
