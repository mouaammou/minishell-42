/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:35:16 by drtaili           #+#    #+#             */
/*   Updated: 2022/12/04 02:20:24 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	func1(const char *format, va_list ap, size_t i)
{
	int	ret;

	ret = 0;
	if (format[i] == 'c')
		ret += ft_putchar(va_arg(ap, int));
	else if (format[i] == 's')
		ret += ft_putstr(va_arg(ap, char *));
	else if (format[i] == 'd' || format[i] == 'i')
		ret += ft_putnbr(va_arg(ap, int));
	else if (format[i] == 'u')
		ret += ft_putnbr_u(va_arg(ap, unsigned int));
	return (ret);
}

int	func2(const char *format, va_list ap, size_t i)
{
	int	ret;

	ret = 0;
	if (format[i] == 'x')
		ret += ft_puthexa(va_arg(ap, unsigned int));
	else if (format[i] == 'X')
		ret += ft_put_hexamaj(va_arg(ap, unsigned int));
	else if (format[i] == 'p')
	{
		ret += ft_putstr("0x");
		ret += ft_puthexa((unsigned long)va_arg(ap, void *));
	}
	return (ret);
}

int	ft_check(const char *format, va_list ap, int i)
{
	int	ret;

	ret = 0;
	if (format[i] == 'c' || format[i] == 's'
		|| format[i] == 'd' || format[i] == 'i' || format[i] == 'u')
		ret += func1(format, ap, i);
	else if (format[i] == 'x' || format[i] == 'X' || format[i] == 'p')
		ret += func2(format, ap, i);
	else
		ret += ft_putchar(format[i]);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	va_start(ap, format);
	ret = 0;
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			while (format[++i] == ' ')
				;
			if (format[i] == '\0')
				break ;
			ret += ft_check(format, ap, i);
		}
		else
			ret += ft_putchar(format[i]);
	}
	va_end(ap);
	return (ret);
}
