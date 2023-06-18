/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:22:32 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/14 22:37:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(int fd, const char *format, ...);
int		ft_puthexa(unsigned long n, int fd);
int		ft_put_hexamaj(unsigned int n, int fd);
int		ft_putnbr(int n, int fd);
int		ft_putnbr_u(unsigned int n, int fd);
int		ft_putchar(char c, int fd);
int		ft_putstr(char *s, int fd);

#endif
