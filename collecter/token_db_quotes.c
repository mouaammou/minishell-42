/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_db_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/26 18:44:41 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	handle_tokens(char *str, int *i, t_list **new_list)
{
	while (str[*i])
	{
		if (is_str(str[*i]))
			token_word(new_list, str, i, QUOTE);
		else if (str[*i] == '$' && str[*i + 1] != '$' && str[*i + 1] != '?')
			token_var(new_list, str, i, QUOTE);
		else if (str[*i] == '$' && str[*i + 1] == '$')
			token_db_dollar(new_list, i, QUOTE);
		else if (str[*i] == '$' && str[*i + 1] == '?')
			token_qts_mark(new_list, i, QUOTE);
		else if (str[*i] == '\'')
		{
			if (!token_quotes(new_list, str, i, QUOTE))
				return ;
		}
		else if (str[*i] == '\"')
		{
			if (!token_quotes(new_list, str, i, QUOTE))
				return ;
		}
		else if (!is_str(str[*i]))
			token_spechars(new_list, str, i);
	}
}

t_list	*token_dbquotes(t_list *tokenizer)
{
	t_list	*new_list;
	int		i;

	new_list = NULL;
	while (tokenizer)
	{
		if (tokenizer->content->token == QUOTE)
		{
			i = 0;
			handle_tokens(tokenizer->content->str, &i, &new_list);
		}
		else
			ft_lstadd_back(&new_list, ft_lstnew(tokenizer->content));
		tokenizer = tokenizer->next;
	}
	return (new_list);
}
