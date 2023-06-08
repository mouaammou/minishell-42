/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:18:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 04:46:52 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/parsing.h"

void	display(t_voidlst *h_list)
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
			t_token *token1 = cmds->content;
			printf("\t[%s]  token: %d\n", token1->str, token1->token);
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

void	display_args(t_voidlst *h_list)
{
	int i = 1;
	while (h_list)
	{
		t_command *tmp = h_list->content;
		char		**cmds = tmp->args;
		t_voidlst	*redirs = tmp->redirections;
		printf("command: %d\n", i);
		while (*cmds)
		{
			printf("\t{%s}\n", *cmds);
			cmds++;
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
	t_list		*head;
	char		*str;
	char		*trimed_str;
	t_list		*expander_list;
	t_voidlst	*commands;
	t_voidlst	*myenv;

	(void)ac;
	(void)av;
	atexit (leaks);
	while (1)
	{
		head = NULL;
		str = readline("\033[6;32mminishell>> :\033[0m");
		add_history(str);
		trimed_str = ft_strtrim(str, " ");
		if (!give_tokens(&head, trimed_str))
		{
			myfree_func(head, trimed_str, str);
			continue;
		}
		if (!compiler(head))
		{
			myfree_func(head, trimed_str, str);
			continue;
		}
		free(str);
		free(trimed_str);
		head = esc_sp_after_spechar(head);
		myenv = take_env(env);
		expander_list = bash_expander(head, myenv);
		free_myenv(myenv);
		commands = bash_concate(expander_list);
		commands = parse_to_args(commands);
		display_args(commands);
		// free_big_list(commands);
		// commands = NULL;
	}
	return (0);
}
