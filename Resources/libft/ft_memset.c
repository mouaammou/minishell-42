/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:10:10 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/18 22:55:23 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	val;
	size_t			i;

	ptr = (unsigned char *)b;
	val = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ptr[i] = val;
		i++;
	}
	return (b);
}
