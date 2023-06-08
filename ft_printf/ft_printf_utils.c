/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:38:16 by drtaili           #+#    #+#             */
/*   Updated: 2022/12/04 02:20:56 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define HEXAMAJ "0123456789ABCDEF"
#define HEXAMIN "0123456789abcdef"

int	ft_putnbr(int n)
{
	unsigned int	nb;
	int				ret;

	ret = 0;
	nb = (unsigned int)n;
	if (n < 0)
	{
		ret += ft_putchar('-');
		nb = n * -1;
	}
	if (nb <= 9)
		ret += ft_putchar(nb + '0');
	else
	{
		ret += ft_putnbr(nb / 10);
		ret += ft_putchar((nb % 10) + '0');
	}
	return (ret);
}

int	ft_putnbr_u(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n < 0)
	{
		ret += ft_putchar('-');
		n = n * -1;
	}
	if (n <= 9)
		ret += ft_putchar(n + '0');
	else
	{
		ret += ft_putnbr_u(n / 10);
		ret += ft_putchar((n % 10) + '0');
	}
	return (ret);
}

int	ft_puthexa(unsigned long n)
{
	int		ret;

	ret = 0;
	if (n < 0)
	{
		ret += ft_putchar('-');
		n = n * -1;
	}
	if (n <= 15)
		ret += ft_putchar(HEXAMIN[n]);
	else
	{
		ret += ft_puthexa(n / 16);
		ret += ft_putchar(HEXAMIN[n % 16]);
	}
	return (ret);
}

int	ft_put_hexamaj(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n < 0)
	{
		ret += ft_putchar('-');
		n = n * -1;
	}
	if (n <= 15)
		ret += ft_putchar(HEXAMAJ[n]);
	else
	{
		ret += ft_put_hexamaj(n / 16);
		ret += ft_putchar(HEXAMAJ[n % 16]);
	}
	return (ret);
}
