/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:12:08 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/13 03:04:58 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	nlen;
	char	*ptr;

	if (!(*needle))
		return ((char *)haystack);
	if (len == 0 || !(*haystack))
		return (NULL);
	nlen = ft_strlen(needle);
	ptr = ft_strchr(haystack, needle[0]);
	i = ptr - haystack;
	while (ptr && i + nlen - 1 < len)
	{
		if (!ft_strncmp(ptr, needle, nlen))
			return (ptr);
		ptr = ft_strchr(ptr + 1, needle[0]);
		if (ptr)
			i = ptr - haystack;
	}
	return (NULL);
}
