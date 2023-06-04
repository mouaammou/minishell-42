/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collecter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:12:11 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/19 18:36:25 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	display_collecter(t_voidlst *h_list)
{
	int i = 1;
	while (h_list)
	{
		t_cmds *tmp = h_list->content;
		t_voidlst	*cmds = tmp->commands;
		t_voidlst	*redirs = tmp->redirects;
		printf("command: %d\n", i);
		while (cmds)
		{
			t_token *mytoken = cmds->content;
			printf("\t[%s] -- token [%d]\n", mytoken->str, mytoken->token);
			cmds = cmds->next;
		}
		printf("\nredirects\n");
		while (redirs)
		{
			t_token *mytoken1 = redirs->content;
			printf("\t[%s]  token: [%d]\n", mytoken1->str, mytoken1->token);
			redirs = redirs->next;
		}
		printf("\n");
		i++;
		h_list = h_list->next;
	}
}

void	leaks (void)
{
	system("leaks minishell");
}

void	affiche(t_list *head)
{
	while (head)
	{
		printf("[%s] == token [%d]\n", head->content->str, head->content->token);
		head = head->next;
	}
}



int	main(int ac, char **av, char **env)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;
	t_list	*newhead;


	// while ((str = readline("minishell>>: ")) != NULL)
	// {
	// 	if (str[0] != 0)
	// 	{
	// 		printf("%s\n", str);
	// 	}
	// 	add_history(str);
	// }
	// exit (0);
	// atexit(leaks);
	head = NULL;
	(void)ac;
	(void)av;
	str = readline("minishell>>: ");
	add_history(str);
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str, 0))
		return (myfree_func(head, trimed_str, str), 11);
	// if (!compiler(head))
	// 	return (myfree_func(head, trimed_str, str), 12);
	newhead = esc_sp_after_spechar(head);
	// newhead = token_dbquotes(newhead);
	newhead = concatenate_strings(newhead);
	// newhead = token_dbquotes(newhead);
	// affiche(newhead);
	// exit (0);
	// //test the collecter of all tokens
	t_voidlst *mylista = bash_collecter(newhead, take_env(env));
	display_collecter(mylista);
	// test the collecter of all tokens
	return (0);
}
