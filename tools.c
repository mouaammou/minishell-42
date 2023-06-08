/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:45:14 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/08 02:00:59 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return -1;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{	
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*none_null_string(char const *str)
{
	char	*s;

	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!s)
		return (NULL);
	ft_strlcpy(s, str, ft_strlen(str) + 1);
	return (s);
}

char	*ft_strjoin_export(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*s;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (none_null_string(s2));
	if (!s2)
		return (none_null_string(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, len1 + len2 + 1);
	ft_strlcat(s, s2, len1 + len2 + 1);
	return (s);
}

void	sort_list(t_list_env *list)
{
	t_list_env	*i;
	t_list_env	*j;
	t_env		swap;

	i = list;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (ft_strcmp(j->data.key, i->data.key) < 0)
			{
				swap = i->data;
				i->data = j->data;
				j->data = swap;
			}
			j = j->next;
		}
		i = i->next;
	}
}
