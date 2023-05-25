/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/23 21:37:16 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	give_tokens(t_list **tokenizer, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_str(str[i]))
			token_word(tokenizer, str, &i);
		else if (str[i] == '$')
			token_var(tokenizer, str, &i);
		else if (str[i] == '\'')
		{
			if (!token_quotes(tokenizer, str, &i, '\''))
				return (0);
		}
		else if (str[i] == '\"')
		{
			if (!token_quotes(tokenizer, str, &i, '\"'))
				return (0);
		}
		else if (!is_str(str[i]))
			token_spechars(tokenizer, str, &i);
	}
	return (1);
}

// void	var_in_quotes(t_list *tokenizer)
// {
// 	while (tokenizer)
// 	{
// 		if (tokenizer->content->token == QUOTE)
// 		{

// 		}
// 	}
// }
