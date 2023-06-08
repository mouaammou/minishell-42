/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:31:05 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/07 23:32:31 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	token_db_dollar(t_list **mylist, int *i, int token)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (0);
	(*i) += 2;
	mytoken->str = ft_strdup("$$");
	mytoken->token = token;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)) , 1);
	return (0);
}

int	token_qts_mark(t_list **mylist, int *i, int token)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (0);
	(*i) += 2;
	mytoken->str = ft_strdup("$?");
	mytoken->token = token;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)), 1);
	return (0);
}

int	myspechars(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '$' || c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	tokens_part_1(t_list **tokenizer, char *str, int *i)
{
	if (ft_isalnum(str[*i]) || !myspechars(str[*i]))
	{
		if (!set_token_word(tokenizer, i, str))
			return (0);
	}
	else if (str[*i] == '$' && str[*i + 1] != '$' && str[*i + 1] != '?')
	{
		if (!set_token_var(tokenizer, i, str))
			return (0);
	}
	else if (str[*i] == '$' && str[*i + 1] == '$')
	{
		if (!token_db_dollar(tokenizer, i, DB_DLR))
			return (0);
	}
	else if (str[*i] == '$' && str[*i + 1] == '?')
	{
		if (!token_qts_mark(tokenizer, i, QST_MARK))
			return (0);
	}
	return (1);
}

int	tokens_part_2(t_list **tokenizer, char *str, int *i)
{
	if (str[*i] == '\'')
	{
		if (!token_quotes(tokenizer, str, i, S_QUOTE))
			return (0);
	}
	else if (str[*i] == '\"')
	{
		if (!token_quotes(tokenizer, str, i, QUOTE))
			return (0);
	}
	else if (str[*i] != '$'  && myspechars(str[*i]))
	{
		if (!token_spechars(tokenizer, str, i))
			return (0);
	}
	return (1);
}
