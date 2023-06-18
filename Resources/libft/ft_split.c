/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:38:23 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/19 02:34:20 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	int		count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static void	ft_free(char **ret, int k)
{
	int	j;

	j = 0;
	while (j < k)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

static int	skip_c(char const *s, char c, int i)
{
	while (s[i] == c && s[i])
		i++;
	return (i);
}

static int	ft_lenword(char const *s, char c, int i)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ret;
	int		word_count;

	word_count = count_words(s, c);
	ret = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	k = -1;
	i = 0;
	while (++k < word_count)
	{
		i = skip_c(s, c, i);
		j = ft_lenword(s, c, i);
		ret[k] = ft_substr(s, i, j - i);
		if (!ret[k])
		{
			ft_free(ret, k);
			return (NULL);
		}
		i = j;
	}
	return (ret);
}
