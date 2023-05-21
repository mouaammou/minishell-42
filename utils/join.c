/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:46:40 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/20 14:49:27 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	total_len(int size, char **strs, char *sep)
{
	int	length;
	int	i;

	i = 1;
	length = 0;
	while (i < size)
		length += len(strs[i++]);
	length += (size - 2) * len(sep);
	return (length);
}

char	*join_sep(int size, char **strs, char *sep)
{
	int		len;
	char	*join;
	int		i;
	int		j;

	if (!size || !strs || !sep)
		return (0);
	join = malloc(sizeof (char) * total_len(size, strs, sep) + 1);
	if (!join)
		return (NULL);
	i = 0;
	len = 0;
	while (++i < size)
	{
		j = 0;
		while (strs[i][j])
			join[len++] = strs[i][j++];
		j = 0;
		while (sep[j] && i < size - 1)
			join[len++] = sep[j++];
	}
	join[len] = 0;
	return (join);
}
