/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:21:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/21 03:18:54 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

t_token	*new_token(char *str, int token)
{
	t_token	*mytoken;

	mytoken = malloc(sizeof (t_token));
	if (!mytoken)
		return (NULL);
	mytoken->str = ft_strdup(str);
	mytoken->token = token;
	return (mytoken);
}

t_voidlst	*new_sublist(char **split, char *str)
{
	t_voidlst	*head;
	int			i;

	i = 0;
	head = NULL;
	if (ft_isspace(str[0]))
		add_back(&head, new_node(new_token(" ", ESP)));
	while (split && split[i])
	{
		add_back(&head, new_node(new_token(split[i], WORD)));
		if (split[i + 1])
			add_back(&head, new_node(new_token(" ", ESP)));
		i++;
	}
	if (ft_isspace(str[ft_strlen(str) - 1]))
		add_back(&head, new_node(new_token(" ", ESP)));
	free_all(split);
	return (head);
}

int	index_of_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	str_cmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
