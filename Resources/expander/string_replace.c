/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:31:45 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/18 00:17:03 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*search_and_replace(t_token **mytoken, t_list_env *myenv)
{
	int			index;
	char		*string_key;
	char		*string_value;

	string_value = NULL;
	if ((*mytoken)->token == QUOTE)
		(*mytoken)->str = replace_all((*mytoken)->str, myenv);
	else
	{
		index = index_of_char((*mytoken)->str, '$');
		string_key = token_var((*mytoken)->str, &index, index);
		string_value = search_for_key(string_key + 1, myenv);
		(*mytoken)->str = string_replace((*mytoken)->str,
				string_key, string_value);
	}
	return (string_value);
}

char	*replace_all(char *old_str, t_list_env *myenv)
{
	int			index;
	char		*string_key;
	char		*string_value;

	index = string_index(old_str, '$', 0);
	while (index != -1)
	{
		string_value = get_string_value(old_str, &index, &string_key, myenv);
		if (!old_str[index])
			break ;
		if (!string_value)
		{
			string_value = ft_strdup("");
			index--;
		}
		old_str = string_replace(old_str, string_key, string_value);
		if (index < 0)
			break ;
		if (!old_str[index])
			break ;
		index++;
		index = string_index(old_str, '$', index);
	}
	return (old_str);
}

char	*var_string(char *str, int i, int start)
{
	int	j;

	j = 0;
	if (ft_isdigit(str[i + 1]) || str[i + 1] == '?')
	{
		i++;
		j++;
	}
	else
	{
		while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))
			j++;
	}
	return (ft_substr(str, start, j + 1));
}

int	string_index(char *str, char c, int i)
{
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_str_search_index(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;

	i = 0;
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (0);
	while (haystack[i] != '\0' && i < len)
	{
		c = 0;
		while (haystack[i + c] != '\0' && needle[c] != '\0'
			&& haystack[i + c] == needle[c] && i + c < len)
			c++;
		if (c == n_len)
			return (i);
		i++;
	}
	return (-1);
}
