/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:21 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/14 16:15:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	grammar :
	test1: PIPE
		- pipe should not be in the beginning or the end of the cmd
		- pipe should be around two commands
	test2: >
	- > should be in the beginning of the command
	- > should not be in the end of the command
*/
#include "tokenizer.h"

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
	if (flag != 0)
		if (prev == mytoken1)
			return (0);
	if (flag != 1)
		if (next == mytoken2)
			return (0);
	return (1);
}

int	syntax_error(char *str, char *token_value)
{
	printf("%s'%s'\n", str, token_value);
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
		if (token_var == PIPE && !check_token(newlist, WHATEVER, WHATEVER, BOTH))
			return (syntax_error("Syntax Error near: ", token_str));
		if (token_var == RE_OUT && !check_token(newlist, WHATEVER, WHATEVER, PREV))
			return (syntax_error("Syntax Error near: ", token_str));
		if (token_var == RE_IN && !check_token(newlist, WHATEVER, WHATEVER, PREV))
			return (syntax_error("Syntax Error near: ", token_str));
		if (token_var == HERE_DOC && !check_token(newlist, WHATEVER, WHATEVER, PREV))
			return (syntax_error("Syntax Error near: ", token_str));
		if (token_var == RE_APPEND && !check_token(newlist, WHATEVER, WHATEVER, PREV))
			return (syntax_error("Syntax Error near: ", token_str));
		newlist = newlist->next;
	}
	return (1);
}

t_list	*ighnore_space(t_list *head)
{
	t_list	*new_lst;

	new_lst = NULL;
	if (!head)
		return (NULL);
	while (head)
	{
		if (head->content->token != ESP)
			ft_lstadd_back(&new_lst, ft_lstnew(head->content));
		head = head->next;
	}
	return (new_lst);
}

void	compiler(t_list *head)
{
	t_list	*new_lst;

	new_lst = ighnore_space(head);
	check_syntax(new_lst);
	free_nodes(new_lst);
}

void	leaks(void)
{
	system ("leaks minishell");
}

int main()
{
	t_list	*head;
	char	*str;
	char	*trimed_str;
	// atexit (leaks);
	head = NULL;
	str = readline("minishell>> :");
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (myfree_func(head, trimed_str, str), 1);
	compiler(head);
	return (myfree_func(head, trimed_str, str));
}
