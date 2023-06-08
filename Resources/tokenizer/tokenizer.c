/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 02:11:57 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	give_tokens(t_list **tokenizer, char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!tokens_part_1(tokenizer, str, &i))
			return (0);
		else if (!tokens_part_2(tokenizer, str, &i))
			return (0);
	}
	return (1);
}
