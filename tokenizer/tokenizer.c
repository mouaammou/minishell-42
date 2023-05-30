/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/30 14:52:57 by mouaammo         ###   ########.fr       */
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

int	tokens_part_1(t_list **tokenizer, char *str, int *i, int flag)
{
	int	mytoken;

	mytoken = QUOTE;
	if (ft_isalnum(str[*i]) || !myspechars(str[*i]))
	{
		if (!flag)
			mytoken = WORD;
		if (!set_token_word(mytoken, tokenizer, i, str))
			return (0);
	}
	else if (str[*i] == '$' && str[*i + 1] != '$' && str[*i + 1] != '?')
	{
		if (!flag)
			mytoken = DLR;
		if (!set_token_var(mytoken, tokenizer, i, str))
			return (0);
	}
	else if (str[*i] == '$' && str[*i + 1] == '$')
	{
		if (!flag)
			mytoken = DLR;
		if (!token_db_dollar(tokenizer, i, mytoken))
			return (0);
	}
	else if (str[*i] == '$' && str[*i + 1] == '?')
	{
		if (!flag)
			mytoken = QST_MARK;
		if (!token_qts_mark(tokenizer, i, mytoken))
			return (0);
	}
	return (1);
}

int	tokens_part_2(t_list **tokenizer, char *str, int *i, int flag)
{
	int	mytoken;

	mytoken = QUOTE;
	if (str[*i] == '\'')
	{
		if (!flag)
			mytoken = S_QUOTE;
		if (!token_quotes(tokenizer, str, i, mytoken))
			return (0);
	}
	else if (str[*i] == '\"')
	{
		if (!token_quotes(tokenizer, str, i, QUOTE))
			return (0);
	}
	else if (str[*i] != '$'  && myspechars(str[*i]))
	{
		if (!token_spechars(tokenizer, str, i, flag))
			return (0);
	}
	return (1);
}

int	give_tokens(t_list **tokenizer, char *str, int flag)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!tokens_part_1(tokenizer,str, &i, flag))
			return (0);
		else if (!tokens_part_2(tokenizer, str, &i, flag))
			return (0);
	}
	return (1);
}

