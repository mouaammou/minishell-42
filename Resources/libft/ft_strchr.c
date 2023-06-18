/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:55:00 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/10 23:01:57 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	size_t	len;
	size_t	i;

	chr = (char)c;
	len = ft_strlen(s);
	if (len == 0)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		if (*s == chr)
			return ((char *)s);
		s++;
		i++;
	}
	return (NULL);
}
