/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_spechars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:03:50 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/01 23:39:06 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_token	*get_quotes_content(char *str, int *i, char qts)
{
	int		j;
	int		start;
	t_token	*mytoken;

	(*i)++;
	j = 0;
	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (NULL);
	while (str[*i] && str[*i] != qts)
	{
		(*i)++;
		j++;
	}
	if (str[*i] == qts)
		(*i)++;
	else
		return (free(mytoken), msg_error("Err: quotes not close"));
	mytoken->str = ft_substr(str, start, j);
	return (mytoken);
}

int	token_quotes(t_list **mylist, char *str, int *i, int token)
{
	t_token	*mytoken;

	mytoken = get_quotes_content(str, i, str[*i]);
	if (!mytoken)
		return (0);
	mytoken->token = token;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)) , 1);
	return (0);
}

int	tokeni_mychar(t_list **mylist, char *str, int *i, int value)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (0);
	if (value == HERE_DOC || value == RE_APPEND)
		mytoken->str = ft_substr(str, *i, 2);
	else
		mytoken->str = ft_substr(str, *i, 1);
	mytoken->token = value;
	(*i)++;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)) , 1);
	return (0);
}

int	spechars_pase_1(t_list **mylist, char *str, int *i, int flag)
{
	int	mytoken;

	mytoken = QUOTE;
	if (str[*i] == '|')
	{
		if (!flag)
			mytoken = PIPE;
		if (!tokeni_mychar(mylist, str, i, mytoken))
			return (0);
	}
	else if (str[*i] == ' ')
	{
		if (!flag)
			mytoken = ESP;
		if (!tokeni_mychar(mylist, str, i, mytoken))
			return (0);
	}
	else if (str[*i] == '<' && str[(*i) + 1] == '<')
	{
		if (!tokeni_mychar(mylist, str, i, HERE_DOC))
			return (0);
		(*i)++;
	}
	return (1);
}

int	spechars_pase_2(t_list **mylist, char *str, int *i, int flag)
{
	int	mytoken;

	mytoken = QUOTE;
	if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		if (!tokeni_mychar(mylist, str, i, RE_APPEND))
			return (0);
		(*i)++;
	}
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
	{
		if (!flag)
			mytoken = RE_IN;
		if (!tokeni_mychar(mylist, str, i, mytoken))
			return (0);
	}
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
	{
		if (!flag)
			mytoken = RE_OUT;
		if (!tokeni_mychar(mylist, str, i, mytoken))
			return (0);
	}
	return (1);
}

int	token_spechars(t_list **mylist, char *str, int *i, int flag)
{
	if (!spechars_pase_1(mylist, str, i, flag))
		return (0);
	else if (!spechars_pase_2(mylist, str, i, flag))
		return (0);
	return (1);
}

