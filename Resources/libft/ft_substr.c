/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:04:17 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/19 02:12:47 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	maxlen;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_strdup(""));
	maxlen = slen - start;
	if (len < slen - start)
		maxlen = len;
	sub = (char *)malloc(maxlen + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, maxlen + 1);
	return (sub);
}
