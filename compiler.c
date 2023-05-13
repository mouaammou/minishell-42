/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:21 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/13 22:02:49 by mouaammo         ###   ########.fr       */
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

int	check_token(t_list *node, int mytoken1, int mytoken2)
{
	int	next;
	int	prev;

	if (node->next)
		next = node->next->content->token;
	else
		next = TOKEN_ERROR;
	if (node->prev)
		prev = node->prev->content->token;
	else
		prev = TOKEN_ERROR;
	if (!(prev == mytoken1 && next == mytoken2))
		return (0);
	return (1);
}

int	syntax_error(char *str, char *token_value)
{
	printf("%s'%s'\n", str, token_value);
	return (0);
}

int	check_syntax(t_list *head)
{
	int		token_var;
	char	*token_str;

	while (head)
	{
		token_var = head->content->token;
		token_str = head->content->str;
		if (token_var == PIPE && !check_token(head, WORD, WORD))
			return (syntax_error("Syntax error near: ", token_str));
		else if (token_var == RE_OUT && !check_token(head, WORD, WORD))
			return (syntax_error("Syntax error near: ", token_str));
		else if (token_var == RE_IN && !check_token(head, TOKEN_ERROR, WORD))
			return (syntax_error("Syntax error near: ", token_str));
		else if (token_var == HERE_DOC && !check_token(head, WORD, WORD))
			return (syntax_error("Syntax error near: ", token_str));
		head = head->next;
	}
	return (1);
}

void	ighnore_space(t_list *head)
{
	while (head)
	{
		if (head->content->token == ESP)
			head->content->token = WORD;
		head = head->next;
	}
}

int	compiler(t_list *head)
{
	int	checked_token;

	ighnore_space(head);
	if (!check_syntax(head))
		return (0);
	return (1);
}

int main()
{
	t_list	*head;
	char	*str;
	char	*trimed_str;

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
