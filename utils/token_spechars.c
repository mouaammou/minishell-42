/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_spechars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:03:50 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/12 17:05:00 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (free(mytoken), msg_error("quotes open"));
	mytoken->str = ft_substr(str, start, j);
	return (mytoken);
}

int	token_quotes(t_list **mylist, char *str, int *i, char qts)
{
	t_token	*mytoken;

	mytoken = get_quotes_content(str, i, qts);
	if (!mytoken)
		return (0);
	if (mytoken->str)
	{
		mytoken->token = QUOTE;
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
	}
	return (1);
}

void	tokeni_mychar(t_list **mylist, int *i, int value)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	mytoken->str = NULL;
	mytoken->token = value;
	(*i)++;
	ft_lstadd_back(mylist, ft_lstnew(mytoken));
}

void	token_spechars(t_list **mylist, char *str, int *i)
{
	if (str[*i] == '|')
		tokeni_mychar(mylist, i, PIPE);
	else if (str[*i] == ' ')
		tokeni_mychar(mylist, i, ESP);
	else if (str[*i] == '<' && str[(*i) + 1] == '<')
	{
		(*i)++;
		tokeni_mychar(mylist, i, HERE_DOC);
	}
	else if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		(*i)++;
		tokeni_mychar(mylist, i, RE_OUT_A);
	}
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
		tokeni_mychar(mylist, i, RE_IN);
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
		tokeni_mychar(mylist, i, RE_OUT);
}
