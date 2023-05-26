/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:03:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/26 20:14:20 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_str(char mychar)
{
	if (mychar != '|' && mychar != '<' && mychar != '>' && mychar != '$'
		&& mychar != '\'' && mychar != '\"' && mychar != ' ')
		return (1);
	return (0);
}

void	token_word(t_list **mylist, char *str, int *i, int token)
{
	int		j;
	int		start;
	t_token	*mytoken;

	j = 0;
	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	while (str[(*i)] && is_str(str[(*i)]))
	{
		(*i)++;
		j++;
	}
	mytoken->str = ft_substr(str, start, j);
	if (mytoken->str)
	{
		mytoken->token = token;
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
	}
}

void	token_var(t_list **mylist, char *str, int *i, int token)
{
	int		j;
	int		start;
	t_token	*mytoken;

	j = 0;
	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	(*i)++;
	while (str[(*i)] &&( ft_isalnum(str[*i]) ||  str[*i] == '_'))
	{
		(*i)++;
		j++;
	}
	mytoken->str = ft_substr(str, start, j + 1);
	mytoken->token = token;
	if (mytoken->str)
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
}
