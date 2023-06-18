/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:06:47 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/16 23:21:57 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenint(long n)
{
	size_t	i;

	i = 0;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i + 1);
}

char	*ft_itoa(int n)
{
	size_t		i;
	char		*a;
	long		nb;

	nb = (long)n;
	i = ft_strlenint(nb);
	a = malloc(ft_strlenint(nb) + 1);
	if (a == NULL)
		return (NULL);
	a[i--] = 0;
	if (nb == 0)
		a[0] = '0';
	if (nb < 0)
	{
		a[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		a[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (a);
}
