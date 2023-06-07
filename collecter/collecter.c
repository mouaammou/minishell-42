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

char	*concate_strings(t_list **command)
{
	t_token		*mytoken1;
	char		*join;

	join = NULL;
	while ((*command) && (mytoken1 = (*command)->content) && is_word(mytoken1->token))
	{
		join = ft_strjoin(join, mytoken1->str);
		(*command) = (*command)->next;
	}
	return (join);
}

void	fill_mylist(t_list **expander, t_cmds **mynode_cmd)
{
	t_token		*mytoken;
	char		*concate_str;

	*mynode_cmd = node_collecter((t_cmds){NULL, NULL});
	while ((*expander) && (*expander)->content->token != PIPE)
	{
		mytoken = (*expander)->content;
		if (is_word(mytoken->token) || mytoken->token == ESP)
		{
			if ((concate_str = concate_strings(expander)))
				add_back(&((*mynode_cmd)->commands), new_node(new_token(concate_str, WORD)));
			else
				add_back(&((*mynode_cmd)->commands), new_node(new_token(mytoken->str, mytoken->token)));
		}
		else
			add_back(&((*mynode_cmd)->redirects), new_node(new_token(mytoken->str, mytoken->token)));
		if ((*expander))
			(*expander) = (*expander)->next;
	}
}

t_voidlst	*bash_concate(t_list *expander)
{
	t_cmds		*mynode_cmd;
	t_voidlst	*parent_list;

	mynode_cmd = NULL;
	parent_list = NULL;
	while (expander)
	{
		fill_mylist(&expander, &mynode_cmd);
		add_back(&parent_list, new_node(mynode_cmd));
		if (expander)
			expander = expander->next;
	}
	return (free_linked_list(expander), parent_list);
}

int	main(int ac, char **av, char **env)
{
	t_list		*head;
	char		*str;
	char		*trimed_str;
	t_list		*expander_list;
	t_voidlst	*commands;

	(void)ac;
	(void)av;
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
		head = esc_sp_after_spechar(head);
		expander_list = bash_expander(head, take_env(env));

		// affiche(expander_list);
		/* CONCATENATION */
		commands = bash_concate(expander_list);
		/* CONCATENATION */
		display_collecter(commands);
	}
	return (0);
}
