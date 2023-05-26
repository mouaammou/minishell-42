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

void	token_db_dollar(t_list **mylist, int *i, int token)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	(*i) += 2;
	mytoken->str = ft_strdup("$");
	mytoken->token = token;
	if (mytoken->str)
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
}

void	token_qts_mark(t_list **mylist, int *i, int token)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	(*i) += 2;
	mytoken->str = ft_itoa(1337);
	mytoken->token = token;
	if (mytoken->str)
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
}

int	give_tokens(t_list **tokenizer, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_str(str[i]))
			token_word(tokenizer, str, &i, WORD);
		else if (str[i] == '$' && str[i + 1] != '$' && str[i + 1] != '?') // handle dollar sign
			token_var(tokenizer, str, &i, DLR);
		else if (str[i] == '$' && str[i + 1] == '$') // token $$
			token_db_dollar(tokenizer, &i, DLR);
		else if (str[i] == '$' && str[i + 1] == '?') // token $?
			token_qts_mark(tokenizer, &i, QST_MARK);
		else if (str[i] == '\'')
		{
			if (!token_quotes(tokenizer, str, &i, S_QUOTE))
				return (0);
		}
		else if (str[i] == '\"')
		{
			if (!token_quotes(tokenizer, str, &i, QUOTE))
				return (0);
		}
		else if (!is_str(str[i]))
			token_spechars(tokenizer, str, &i);
	}
	return (1);
}

