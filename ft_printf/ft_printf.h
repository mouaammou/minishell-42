/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:22:32 by drtaili           #+#    #+#             */
/*   Updated: 2022/12/04 02:22:50 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_puthexa(unsigned long n);
int		ft_put_hexamaj(unsigned int n);
int		ft_putnbr(int n);
int		ft_putnbr_u(unsigned int n);
int		ft_putchar(char c);
int		ft_putstr(char *s);

#endif
