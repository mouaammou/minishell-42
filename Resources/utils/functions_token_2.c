/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_token_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:26:14 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/04 13:40:11 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*token_word(char *str, int *i, int start)
{
	int	j;

	j = 0;
	while (str[(*i)] && (!myspechars(str[*i])))
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
	if (ft_isdigit(str[*i]))
	{
		j++;
		(*i)++;
	}
	else
	{
		while (str[(*i)] && (ft_isalnum(str[(*i)]) || str[(*i)] == '_'))
		{
			(*i)++;
			j++;
		}
	}
	return (ft_substr(str, start, j + 1));
}

int	set_token_word(t_list **mylist, int *i, char *str)
{
	int		start;
	t_token	*mytoken;

	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (0);
	mytoken->str = token_word(str, i, start);
	mytoken->token = WORD;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)), 1);
	return (0);
}

int	set_token_var(t_list **mylist, int *i, char *str)
{
	int		start;
	t_token	*mytoken;

	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (0);
	mytoken->str = token_var(str, i, start);
	mytoken->token = DLR;
	if (mytoken->str)
		return (ft_lstadd_back(mylist, ft_lstnew(mytoken)), 1);
	return (0);
}

int	token_spechars(t_list **mylist, char *str, int *i)
{
	if (!spechars_pase_1(mylist, str, i))
		return (0);
	else if (!spechars_pase_2(mylist, str, i))
		return (0);
	return (1);
}
