/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 05:41:55 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/17 02:48:59 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	a = (void *)malloc(size * count);
	if (a == NULL)
		return (NULL);
	ft_bzero(a, count * size);
	return (a);
}
