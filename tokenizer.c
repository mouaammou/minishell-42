/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/13 21:21:49 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	display_tokens (t_list *head)
{
	while (head)
	{
		t_token *ftoken = (t_token *) head->content;
		if (ftoken->token  == WORD)
		{
			puts("word");
			printf("[%s]\n", ftoken->str);
		}
		if (ftoken->token  == PIPE)
			puts("PIPE");
		if (ftoken->token  == RE_OUT)
			puts("RE OUTPUT");
		if (ftoken->token  == RE_IN)
			puts("RE INPUT");
		if (ftoken->token  == HERE_DOC)
			puts("HERE_DOC");
		if (ftoken->token  == RE_APPEND)
			puts("RE_O_APEND");
		if (ftoken->token  == ESP)
			puts("ESP");
		if (ftoken->token  == QUOTE)
		{
			puts("QUOTES");
			printf("[%s]\n", ftoken->str);
		}
		if (ftoken->token  == S_QUOTE)
		{
			puts("S_QUOTES");
			printf("[%s]\n", ftoken->str);
		}
		head = head->next;
	}
}
void	display_tokens_back(t_list *head)
{
	while (head)
	{
		t_token *ftoken = (t_token *) head->content;
		if (ftoken->token  == WORD)
		{
			puts("word");
			printf("[%s]\n", ftoken->str);
		}
		if (ftoken->token  == PIPE)
			puts("PIPE");
		if (ftoken->token  == RE_OUT)
			puts("RE OUTPUT");
		if (ftoken->token  == RE_IN)
			puts("RE INPUT");
		if (ftoken->token  == HERE_DOC)
			puts("HERE_DOC");
		if (ftoken->token  == RE_APPEND)
			puts("RE_O_APEND");
		if (ftoken->token  == ESP)
			puts("ESP");
		if (ftoken->token  == QUOTE)
		{
			puts("QUOTES");
			printf("[%s]\n", ftoken->str);
		}
		if (ftoken->token  == S_QUOTE)
		{
			puts("S_QUOTES");
			printf("[%s]\n", ftoken->str);
		}
		head = head->prev;
	}
}

void	leaks()
{
	system ("leaks minishell");
}

// int	main ()
// {
// 	t_list	*head;
// 	char	*str;
// 	char	*trimed_str;
// 	// atexit(leaks);
// 	head = NULL;
// 	str = readline("minishell>> :");
// 	if (!str)
// 		return (0);
// 	trimed_str = ft_strtrim(str, " ");
// 	if (!give_tokens(&head, trimed_str))
// 		return (myfree_func(head, trimed_str, str), 1);
// 	while (head)
// 	{
// 		printf("%s\n", head->content->str);
// 		head = head->next;
// 	}
// 	return (myfree_func(head, trimed_str, str));
// }
