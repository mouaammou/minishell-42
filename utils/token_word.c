/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:03:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/28 22:02:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*token_word(char *str, int *i, int start)
{
	int	j;

	j = 0;
	while (str[(*i)] && (ft_isalnum(str[(*i)]) || !myspechars(str[*i])))
	{
		(*i)++;
		j++;
	}
	return (ft_substr(str, start, j));
}

char	*token_var(char *str, int *i, int start)
{
	int	j;

	j = 0;
	(*i)++;
	while (str[(*i)] && (ft_isalnum(str[(*i)]) ||  str[(*i)] == '_'))
	{
		(*i)++;
		j++;
	}
	return (ft_substr(str, start, j + 1));
}

int	set_token_word(int token, t_list **mylist, int *i, char *str)
{
	int		start;
	t_token	*mytoken;

	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (0);
	mytoken->str = token_word(str, i, start);
	mytoken->token = token;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)), 1);
	return (0);
}

int	set_token_var(int token, t_list **mylist, int *i, char *str)
{
	int		start;
	t_token	*mytoken;

	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (0);
	mytoken->str = token_var(str, i, start);
	mytoken->token = token;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)), 1);
	return (0);
}

