/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 01:03:24 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/13 01:13:48 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;
	size_t	ret;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (!dstsize)
		return (slen);
	len = ft_strlen(dst);
	ret = len + slen;
	if (dstsize <= len)
		return (slen + dstsize);
	while (src[i] && len < dstsize - 1)
	{
		dst[len] = src[i];
		len++;
		i++;
	}
	dst[len] = '\0';
	return (ret);
}
