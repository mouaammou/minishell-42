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

#define RED  "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE  "\033[1;34m"
#define RESET "\033[0m"

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

char	*concate_strings(t_voidlst **cmds)
{
	t_token		*mytoken1;
	char		*join;

	join = NULL;
	while ((*cmds) && (mytoken1 = (*cmds)->content) && is_word(mytoken1->token))
	{
		join = ft_strjoin(join, mytoken1->str);
		(*cmds) = (*cmds)->next;
	}
	return (join);
}

t_voidlst	*bash_concate(t_voidlst	*expander)
{
	t_cmds		*tmp;
	t_voidlst	*cmds;
	t_token		*mytoken;
	char		*concate_str;


	while (expander)
	{

		tmp = expander->content;
		cmds = tmp->commands;
		while (cmds)
		{
			mytoken = cmds->content;
			concate_str = concate_strings(&cmds);
			printf("concate string: %s\n", concate_str);
			if (cmds)
				cmds = cmds->next;
		}

		expander = expander->next;
	}
	
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_list		*head;
	char		*str;
	char		*trimed_str;
	t_list		*newhead;
	t_list	*expander_list;

	g_dollars.two_dollars = "**";
	g_dollars.one_dollar = "+";
	g_dollars.qts_mark = "??";

	(void)ac;
	(void)av;
	while (1)
	{
		head = NULL;
		str = readline("\033[1;35mminishell>> :\033[0m");
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
		newhead = esc_sp_after_spechar(head);
		expander_list = bash_collecter(newhead, take_env(env));

		affiche(expander_list);
		/* CONCATENATION */
		// expander_list = bash_concate(expander_list);
		/* CONCATENATION */
		// display_collecter(expander_list);
	}
	return (0);
}
