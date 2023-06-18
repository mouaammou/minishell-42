/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:45:51 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/14 21:30:36 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	check_token(t_list *node, int mytoken1, int mytoken2, int flag)
{
	int	next;
	int	prev;

	if (node->next)
		next = node->next->content->token;
	else
		next = WHATEVER;
	if (node->prev)
		prev = node->prev->content->token;
	else
		prev = WHATEVER;
	if (flag == PREV)
		if (prev != mytoken1)
			return (0);
	if (flag == NEXT)
		if (next != mytoken2)
			return (0);
	if (flag == BOTH)
		if (prev != mytoken1 || next != mytoken2)
			return (0);
	return (1);
}

int	check_pipe(t_list *node)
{
	int	next;
	int	prev;

	if (node->next)
		next = node->next->content->token;
	else
		next = WHATEVER;
	if (node->prev)
		prev = node->prev->content->token;
	else
		prev = WHATEVER;
	if (prev == WHATEVER || next == WHATEVER || prev == PIPE || next == PIPE)
		return (0);
	return (1);
}

int	syntax_error(char *token_value)
{
	g_global_exit.exit_status = 258;
	ft_printf(2, "minishell: Syntax Error near: %s\n", token_value);
	return (0);
}

int	check_syntax(t_list *newlist)
{
	int		token_var;
	char	*token_str;

	while (newlist)
	{
		token_var = newlist->content->token;
		token_str = newlist->content->str;
		if (token_var == PIPE && !check_pipe(newlist))
			return (syntax_error(token_str));
		if (token_var == RE_OUT && !check_token(newlist, WHATEVER, WORD, NEXT))
			return (syntax_error(token_str));
		if (token_var == RE_IN && !check_token(newlist, WHATEVER, WORD, NEXT))
			return (syntax_error(token_str));
		if (token_var == HERE_DOC
			&& !check_token(newlist, WHATEVER, WORD, NEXT))
			return (syntax_error(token_str));
		if (token_var == RE_APPEND
			&& !check_token(newlist, WHATEVER, WORD, NEXT))
			return (syntax_error(token_str));
		newlist = newlist->next;
	}
	return (1);
}
