/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_token_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:25:53 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/18 00:15:34 by mouaammo         ###   ########.fr       */
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
		return (free(mytoken),
			msg_error("minishell:\033[1;31m quotes not close\033[0m\n"));
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
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)), 1);
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
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)), 1);
	return (0);
}

int	spechars_pase_1(t_list **mylist, char *str, int *i)
{
	if (str[*i] == '|')
	{
		if (!tokeni_mychar(mylist, str, i, PIPE))
			return (0);
	}
	else if (str[*i] == ' ')
	{
		if (!tokeni_mychar(mylist, str, i, ESP))
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

int	spechars_pase_2(t_list **mylist, char *str, int *i)
{
	if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		if (!tokeni_mychar(mylist, str, i, RE_APPEND))
			return (0);
		(*i)++;
	}
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
	{
		if (!tokeni_mychar(mylist, str, i, RE_IN))
			return (0);
	}
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
	{
		if (!tokeni_mychar(mylist, str, i, RE_OUT))
			return (0);
	}
	return (1);
}
