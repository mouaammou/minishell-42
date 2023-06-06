/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:31:45 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/06 02:17:35 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*search_and_replace(t_token **mytoken, t_voidlst *myenv)
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
		(*mytoken)->str = string_replace((*mytoken)->str, string_key, string_value);	
	}
	return (string_value);
}

char	*replace_others_values(char *old_str)
{
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		if (ft_strnstr(old_str, "$$", ft_strlen(old_str)))
		{
			old_str = string_replace(old_str, "$$", g_dollars.two_dollars);
			flag = 1;
		}
		if (ft_strnstr(old_str, "$?", ft_strlen(old_str)))
		{
			old_str = string_replace(old_str, "$?", g_dollars.qts_mark);
			flag = 1;
		}
	}
	return (old_str);
}

char	*replace_all(char *old_str, t_voidlst *myenv)
{
	int			index;
	char		*string_key;
	char		*string_value;
	
	// old_str = replace_others_values(old_str);
	index = string_index(old_str, '$', 0);
	while (index != -1)
	{
		string_key = NULL;
		string_value = NULL;
		string_key = var_string(old_str, index, index);
		if (string_key[0] == '$' && ft_strlen(string_key) == 1)
			string_value = ft_strdup("$");
		else
			string_value = search_for_key(string_key + 1, myenv);
		if (!string_value)
		{
			string_value = ft_strdup("");
			index--;
		}
		old_str = string_replace(old_str , string_key, string_value);
		index++;
		index = string_index(old_str, '$', index);
	}
	return (old_str);
}

char	*var_string(char *str, int i, int start)
{
	int	j;

	j = 0;
	while (str[++i] && (ft_isalnum(str[i]) ||  str[i] == '_'))
		j++;
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

char	*string_replace(char *phrase, char *oldstring, char *newstring)
{
    int		oldlen;
	int		newlen;
	int		phraselen;
	int		index;
	char	*new_phrase;
	int		total_len;

	if (!oldstring || !newstring)
		return (phrase);
	oldlen = ft_strlen(oldstring);
	newlen = ft_strlen(newstring);
	phraselen = ft_strlen(phrase);
	total_len = (phraselen + newlen - oldlen);
	new_phrase = malloc(sizeof (char) * (total_len + 1));
	if (!new_phrase)
		return (NULL);
	index = ft_str_search_index(phrase, oldstring, ft_strlen(phrase));
    ft_memcpy(new_phrase, phrase, index);
    ft_memcpy(new_phrase + index, newstring, newlen);
    ft_memcpy(new_phrase + index + newlen, phrase + index + oldlen, phraselen - index - oldlen);
    new_phrase[total_len] = '\0';
    return (new_phrase);
}


