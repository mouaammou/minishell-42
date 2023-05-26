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

int	str_cmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	count_pipes(t_list *head)
{
	int	count;

	count = 1;
	if (!head)
		count = 0;
	while (head)
	{
		if (head->content->token == PIPE)
			count++;
		head = head->next;
	}
	return (count);
}

void	manage_heredoc(t_list **head, int *fd)
{
	char	*tmp;
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		tmp = ft_strjoin( (*head)->next->content->str, "\n");
		if (!line || !str_cmp(line, tmp))
		{
			ft_putstr_fd("\n", 1);
			break;
		}
		free(tmp);
		write(*fd, line, ft_strlen(line));
	}
}

void	handle_heredoc(t_list **head)
{
	char	*str;
	int		fd;

	str = ft_strjoin("/tmp/", (*head)->next->content->str);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_error("bad file descriptor\n", 3);
	manage_heredoc(head, &fd);
	(*head)->content->token = RE_IN;
	(*head)->content->str = str;
	close (fd);
}

void	display_list(t_voidlst *list)
{
	t_token *mytoken;
	while (list)
	{
		mytoken = list->content;
		printf("--> [%s]", mytoken->str);
		list = list->next;
	}
	printf("\n");
}

void	add_multi_nodes(t_voidlst **origin, t_voidlst *newlist)
{
	while (newlist)
	{
		add_back(origin, new_node(newlist->content));
		newlist = newlist->next;
	}
}

// void	check_commands(t_cmds **tmp_list, t_list **head, t_voidlst *myenv)
// {
// 	t_voidlst	*sublst;
// 	int			mytoken;

// 	sublst = NULL;
// 	mytoken = (*head)->content->token;
// 	if (mytoken == DLR)
// 	{
// 		sublst = expander(*head, myenv);
// 		if (sublst)
// 			add_multi_nodes(&((*tmp_list)->commands), sublst);
// 	}
// 	else if (ft_strchr((*head)->content->str, '$') && mytoken == QUOTE)
// 	{
// 		sublst = expander(*head, myenv);
// 		if (sublst)
// 			add_multi_nodes(&((*tmp_list)->commands), sublst);
// 	}
// 	else
// 		add_back(&((*tmp_list)->commands), new_node((*head)->content));
// }

void	command_expansion(t_voidlst **origin, t_list **head, t_voidlst *myenv, int flag)
{
	t_voidlst	*sublst;
	t_token		*mytoken;

	sublst = NULL;
	mytoken = (*head)->content;
	if (mytoken->token == DLR)
	{
		sublst = expander(*head, myenv);
		if (sublst)
			add_multi_nodes(origin, sublst);
	}
	else if (ft_strchr(mytoken->str, '$') && mytoken->token == QUOTE)
	{
		sublst = expander(*head, myenv);
		if (sublst)
			add_multi_nodes(origin, sublst);
	}
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

void	handle_cmd(t_cmds **tmp_list, t_list **head, t_voidlst *myenv)
{
	int	mytoken;

	*tmp_list = node_collecter((t_cmds){NULL, NULL});
	while ((*head) && (*head)->content->token != PIPE)
	{
		mytoken = (*head)->content->token;
		if (mytoken == WORD || mytoken == QUOTE || mytoken == DLR
		|| mytoken == S_QUOTE || mytoken == ESP || mytoken == QST_MARK)
		{
			if (mytoken == QST_MARK)
				expand_qts_mark(&((*tmp_list)->commands), head);
			else
				command_expansion(&((*tmp_list)->commands), head, myenv, 0);
		}
		else
			command_expansion(&((*tmp_list)->redirects), &(*head)->next, myenv, 1);
		(*head) = (*head)->next;
	}
}

t_cmds *node_collecter(t_cmds args)
{
	t_cmds *new_collecter;

	new_collecter = malloc (sizeof (t_cmds));
	if (!new_collecter)
		ft_error("malloc failed\n", 3);
	new_collecter->commands = args.commands;
	new_collecter->redirects = args.redirects;
	return (new_collecter);
}

t_voidlst	*bash_collecter(t_list *tokenizer, t_voidlst *myenv)
{
	t_voidlst	*collecter;
	t_cmds	*tmp_list;

	collecter = NULL;
	tmp_list = NULL;
	while (tokenizer)
	{
		handle_cmd(&tmp_list, &tokenizer, myenv);
		add_back(&collecter, new_node(tmp_list));
		if (tokenizer && tokenizer->content->token == PIPE)
			tokenizer = tokenizer->next;
	}
	return (collecter);
}

t_list *esc_sp_after_spechar(t_list *head)
{
	t_list	*newlist;

	newlist = NULL;
	while (head)
	{
		if (head->content->token == ESP)
		{
			if (head->prev && (head->prev->content->token == WORD || head->prev->content->token == QUOTE
			|| head->prev->content->token == S_QUOTE || head->prev->content->token == DLR))
			{
				ft_lstadd_back(&newlist, ft_lstnew(head->content));
			}
			head = head->next;
			continue;
		}
		ft_lstadd_back(&newlist, ft_lstnew(head->content));
		head = head->next;
	}
	return (newlist);
}

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

t_list	*token_dbquotes(t_list *tokenizer)
{
	t_list	*new_list;
	char	*str;
	int		i;

	new_list = NULL;
	while (tokenizer)
	{
		if (tokenizer->content->token == QUOTE)
		{
			str = tokenizer->content->str;
			i = 0;
			while (str[i])
			{
				if (is_str(str[i]))
					token_word(&new_list, str, &i, QUOTE);
				else if (str[i] == '$' && str[i + 1] != '$' && str[i + 1] != '?')
					token_var(&new_list, str, &i, QUOTE);
				else if (str[i] == '$' && str[i + 1] == '$') // token $$
					token_db_dollar(&new_list, &i, QUOTE);
				else if (str[i] == '$' && str[i + 1] == '?') // token $?
					token_qts_mark(&new_list, &i, QUOTE);
				else if (str[i] == '\'')
				{
					if (!token_quotes(&new_list, str, &i, QUOTE))
						return (0);
				}
				else if (str[i] == '\"')
				{
					if (!token_quotes(&new_list, str, &i, QUOTE))
						return (0);
				}
			}
		}
		else
			ft_lstadd_back(&new_list, ft_lstnew(tokenizer->content));
		tokenizer = tokenizer->next;
	}
	return (new_list);
}

int	main(int ac, char **av, char **env)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;

	// atexit(leaks);
	head = NULL;
	(void)ac;
	(void)av;
	str = readline("minishell>>: ");
	add_history(str);
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (0);
	compiler(head);
	head = esc_sp_after_spechar(head);

	head = token_dbquotes(head);
	// affiche(head);
	// exit(0);
	// //test the collecter of all tokens
	t_voidlst *mylista = bash_collecter(head, take_env(env));
	display_collecter(mylista);
	// test the collecter of all tokens
	return (0);
}
