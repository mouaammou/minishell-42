/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:18:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/01 18:20:29 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	command_expansion(t_voidlst **origin, t_list **head,
	t_voidlst *myenv, int flag)
{
	t_voidlst	*sublst;
	t_token		*mytoken;

	sublst = NULL;
	mytoken = (*head)->content;
	if (mytoken->token == DLR)
	{
		expander_dollar(head, myenv, origin, flag);
	}
	else if (mytoken->token == QUOTE && ft_strchr(mytoken->str, '$'))
		expander_dbquote(head, myenv, origin, flag);
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
		db_quote_list = db_quote_list->next;
	}
	return (sub_lst);
}
