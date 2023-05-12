/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:05:21 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/12 17:06:13 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	give_tokens(t_list **tokenizer, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_str(str[i]))
			token_word(tokenizer, str, &i);
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
