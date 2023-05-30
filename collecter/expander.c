/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:18:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/30 19:20:01 by mouaammo         ###   ########.fr       */
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
	// if ((mytoken->token == DLR  || mytoken->token == QUOTE)
	// 	&& (!str_cmp(mytoken->str, "$") || !str_cmp(mytoken->str, "$$")))
	// 	add_back(origin, new_node(mytoken));
	// else if (!ft_strchr(mytoken->str, ' '))
	// 	expand_multi_dollars(*head, myenv, origin);
	// else 
	if (mytoken->token == DLR || (ft_strchr(mytoken->str, '$') && mytoken->token == QUOTE))
	{
		sublst = expander_dbquote(*head, myenv);
		if (sublst)
			add_multi_nodes(origin, sublst);
	}
	else
		add_back(origin, new_node(mytoken));
	if (flag)
		(*head) = (*head)->next;
	// if (mytoken->token == DLR)
	// {
	// 	sublst = expander_dollar(*head, myenv);
	// 	if (sublst)
	// 		add_multi_nodes(origin, sublst);
	// }
	// else if (ft_strchr(mytoken->str, '$') && mytoken->token == QUOTE)
	// {
	// 	sublst = expander_dbquote(*head, myenv);
	// 	if (sublst)
	// 		add_multi_nodes(origin, sublst);
	// }
	// else
	// 	add_back(origin, new_node(mytoken));
	// if (flag)
	// 	(*head) = (*head)->next;
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

t_voidlst	*expander_dbquote(t_list *head, t_voidlst *myenv)
{
	char		*searched_str;
	t_voidlst	*sub_lst;
	char 		*join;
	t_list		*db_quote_list;

	db_quote_list = token_dbquotes(ft_lstnew(head->content));
	sub_lst = NULL;
	join = NULL;
	while (db_quote_list)
	{
		// printf("%s\n", db_quote_list->content->str);
		searched_str = search_for_key(db_quote_list->content->str + 1, myenv);
		if (searched_str)
			db_quote_list->content->str = searched_str;
		else if (ft_strchr(db_quote_list->content->str, '$'))
			db_quote_list->content->str = NULL;
		join = ft_strjoin(join, db_quote_list->content->str);
		db_quote_list = db_quote_list->next;
	}
	// exit (0);
	if (join)
		sub_lst = new_node(new_token(join, QUOTE));
	return (sub_lst);
}
void	expand_multi_dollars(t_list *head, t_voidlst *myenv, t_voidlst **origin)
{
	int		i;
	char	**split;
	char	**split_dlr;
	char	*searched_str;
	t_voidlst	*sub_lst;
	
	i = 0;
	split_dlr = ft_split(head->content->str, '$');
	while (split_dlr[i])
	{
		sub_lst = NULL;
		searched_str = search_for_key(split_dlr[i], myenv);
		if (searched_str)
		{
			split = ft_split(searched_str, ' ');
			sub_lst = new_sublist(split);
		}
		// else
		// 	add_back(origin, new_node(new_token(split_dlr[i], WORD)));
		if (sub_lst)
			add_multi_nodes(origin, sub_lst);
		i++;
	}
}
t_voidlst	*expander_dollar(t_list *head, t_voidlst *myenv)
{
	char		**split;
	char		*searched_str;
	t_voidlst	*sub_lst;
	t_token		*mytoken;

	sub_lst = NULL;
	mytoken = (t_token *)head->content;
	searched_str = search_for_key(mytoken->str + 1, myenv);
	if (searched_str)
	{
		split = ft_split(searched_str, ' ');
		sub_lst = new_sublist(split);
	}
	// free(searched_str);
	return (sub_lst);
}
