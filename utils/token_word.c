/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:03:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/20 14:49:27 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_str(char mychar)
{
	if (mychar != '|' && mychar != '<' && mychar != '>'
		&& mychar != '\'' && mychar != '\"' && mychar != ' ')
		return (1);
	return (0);
}

void	token_word(t_list **mylist, char *str, int *i)
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
		mytoken->token = WORD;
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
	}
}
