/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:18:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/04 04:52:18 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"


char	*string_replace(char *phrase, const char *oldstring, const char *newstring)
{
    int		oldlen;
	int		newlen;
	int		phraselen;
	int		i;
	int		index;
	char	*new_phrase;
	int		total_len;
	int		j;

	if (!oldstring || !newstring)
		return (phrase);
	oldlen = ft_strlen(oldstring);
	newlen = ft_strlen(newstring);
	phraselen = ft_strlen(phrase);
	total_len = (phraselen + newlen - oldlen);
	new_phrase = malloc(sizeof (char) * total_len + 1);
	if (!new_phrase)
		return (NULL);
	ft_memcpy(new_phrase, phrase, total_len);
	index = index_of_char(phrase, oldstring[0]);
	i = 0;
	while (i < newlen)
		new_phrase[index++] = newstring[i++];
	new_phrase[index] = '\0';
	j = index_of_char(phrase, oldstring[oldlen - 1]) + 1;
	while (j < total_len)
		new_phrase[index++] = phrase[j++];
	return (new_phrase[j] = '\0', new_phrase);
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

char	*var_string(char *str, int i, int start)
{
	int	j;

	j = 0;
	i++;
	while (str[i] && (ft_isalnum(str[i]) ||  str[i] == '_'))
	{
		i++;
		j++;
	}
	return (ft_substr(str, start, j + 1));
}

char	*replace_all(char *old_str, t_voidlst *myenv)
{
	int			index;
	char		*string_key;
	char		*string_value;
	char		*new_str;

	
	index = string_index(old_str, '$', 0);
	new_str = NULL;
	while (old_str && old_str[index] && index != -1)
	{
		string_key = NULL;
		string_key = var_string(old_str, index, index);
		if (string_key)
		{
			string_value = search_for_key(string_key + 1, myenv);
			if (string_value)
				old_str = string_replace(old_str , string_key, string_value);
		}
		index += 1;
		index = string_index(old_str, '$', index);
	}
	return (old_str);
}

void	expande(t_list *head, t_voidlst *myenv, t_voidlst **origin)
{
	t_token		*mytoken;
	int			index;
	char		*string_key;
	char		*string_value;
	char		**split;
	t_voidlst	*sub_lst;
	
	mytoken = (head)->content;
	if (mytoken->token == QUOTE)
		mytoken->str = replace_all(mytoken->str, myenv);
	else
	{
		index = index_of_char(mytoken->str, '$');
		string_key = token_var(mytoken->str, &index, index);
		string_value = search_for_key(string_key + 1, myenv);
		mytoken->str = string_replace(mytoken->str, string_key, string_value);	
	}
	if (string_value && mytoken->token == DLR)
	{
		split = ft_split(mytoken->str, ' ');
		sub_lst = new_sublist(split, mytoken->token);
		if (sub_lst)
			add_multi_nodes(origin, sub_lst);
	}
	else
		add_back(origin, new_node(mytoken));
}


void	command_expansion(t_voidlst **origin, t_list **head,
	t_voidlst *myenv, int flag)
{
	t_voidlst	*sublst;
	t_token		*mytoken;

	sublst = NULL;
	mytoken = (*head)->content;
	if (mytoken->token == DLR)
	{
		// expander_dollar(head, myenv, origin, flag);
		expande(*head, myenv, origin);
	}
	else if (mytoken->token == QUOTE && ft_strchr(mytoken->str, '$'))
	{
		// expander_dbquote(head, myenv, origin, flag);
		expande(*head, myenv, origin);
	}
	else
		add_back(origin, new_node(mytoken));
	if (flag)
		(*head) = (*head)->next;
}

void	expand_qts_mark(t_voidlst **origin, t_list **head)
{
	t_voidlst	*sublst;
	t_token		*mytoken;

	sublst = NULL;
	mytoken = (*head)->content;
	free(mytoken->str);
	mytoken->str = ft_itoa(1337);
	if (mytoken->str)
		add_back(origin, new_node(mytoken));
}

char	*manage_others(char *str)
{
	if (!str_cmp(str, "$$") || !str_cmp(str, "$"))
		return (str);
	else if (!str_cmp(str, "$?"))
	{
		str = ft_itoa(1337);
		return (str);
	}
	return (NULL);
}

t_voidlst	*expander_dbquote(t_list **head, t_voidlst *myenv, t_voidlst **origin, int flag)
{
	char		*searched_str;
	t_voidlst	*sub_lst;
	char 		*join;
	t_list		*db_quote_list;
	int			token;

	db_quote_list = token_dbquotes(ft_lstnew((*head)->content));
	sub_lst = NULL;
	join = NULL;
	while (db_quote_list)
	{
		token = (*head)->content->token;
		if (flag)
			token = (*head)->prev->content->token;
		
		searched_str = NULL;
		if (ft_strchr(db_quote_list->content->str, '$'))
			searched_str = search_for_key(db_quote_list->content->str + 1, myenv);
		if (searched_str)
			db_quote_list->content->str = searched_str;
		else if (ft_strchr(db_quote_list->content->str, '$') 
				&& !manage_others(db_quote_list->content->str))
			db_quote_list->content->str = NULL;
		join = ft_strjoin(join, db_quote_list->content->str);
		// printf("{%s} == token :%d\n", db_quote_list->content->str, db_quote_list->content->token);
		db_quote_list = db_quote_list->next;
	}
	if (join)
		sub_lst = new_node(new_token(join, token));
	if (sub_lst)
		add_back(origin, sub_lst);
	free(join);
	return (sub_lst);
}


t_voidlst	*expander_dollar(t_list **head, t_voidlst *myenv, t_voidlst **origin, int flag)
{
	char		**split;
	char		*searched_str;
	t_voidlst	*sub_lst;
	t_list		*db_quote_list;
	int			token;

	db_quote_list = token_dbquotes(ft_lstnew((*head)->content));
	while (db_quote_list)
	{
		sub_lst = NULL;
		searched_str = NULL;
		token = (*head)->content->token;
		if (flag)
			token = (*head)->prev->content->token;
		db_quote_list->content->token = token;
		if (ft_strchr(db_quote_list->content->str, '$'))
			searched_str = search_for_key(db_quote_list->content->str + 1, myenv);
		if (searched_str)
		{
			split = ft_split(searched_str, ' ');
			sub_lst = new_sublist(split, token);
			if (sub_lst)
				add_multi_nodes(origin, sub_lst);
		}
		else if (!searched_str && !ft_strchr(db_quote_list->content->str, '$'))
			add_back(origin, new_node(db_quote_list->content));
		else if (manage_others(db_quote_list->content->str))
			add_back(origin, new_node(db_quote_list->content));
		// printf("{%s} == token :%d\n", db_quote_list->content->str, db_quote_list->content->token);
		db_quote_list = db_quote_list->next;
	}
	return (sub_lst);
}
