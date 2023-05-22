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

void	handle_heredoc(t_list **head)
{
	char	*str;
	char	*line;
	int		file_permissions;
	int		fd;

	str = ft_strjoin("/tmp/", (*head)->next->content->str);
	file_permissions = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH;
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, file_permissions);
	if (fd == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, (*head)->next->content->str, ft_strlen(line) - 1))
		{
			ft_putstr_fd("\n", 1);
			break;
		}
		write(fd, line, ft_strlen(line));
	}
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

void	backadd_list(t_voidlst **origin, t_voidlst *newlist)
{
	t_voidlst	*tmp;
	while (newlist)
	{
		tmp = newlist->next;
		add_back(origin, new_node(newlist->content));
		newlist = tmp;
	}
}

void	check_commands(t_cmds **tmp_list, t_list **head, t_voidlst *myenv)
{
	t_voidlst	*sublst;

	sublst = NULL;
	if (ft_strchr((*head)->content->str, '$'))
	{
		sublst = expander(*head, myenv);
		if (sublst)
			backadd_list(&((*tmp_list)->commands), sublst);
	}
	else
		add_back(&((*tmp_list)->commands), new_node((*head)->content));
}

void	check_redirections(t_cmds **tmp_list, t_list **head, t_voidlst *myenv)
{
	if ((*head)->next)
	{
		if (ft_strchr((*head)->next->content->str, '$'))
			(*head)->content->str = search_for_key((*head)->next->content->str, myenv);
		else
			(*head)->content->str = (*head)->next->content->str;
		add_back(&((*tmp_list)->redirects), new_node((*head)->content));
		(*head) = (*head)->next;
	}
}

void	handle_cmd(t_cmds **tmp_list, t_list **head, t_voidlst *myenv)
{
	*tmp_list = node_collecter((t_cmds){NULL, NULL});
	while ((*head) && (*head)->content->token != PIPE)
	{
		if ((*head)->content->token == WORD || (*head)->content->token == QUOTE
		|| (*head)->content->token == S_QUOTE || (*head)->content->token == ESP)
		{
			check_commands(tmp_list, head, myenv);
		}
		else
		{
			check_redirections(tmp_list, head, myenv);
		}
		(*head) = (*head)->next;
	}
}

t_cmds *node_collecter(t_cmds args)
{
	t_cmds *new_collecter;

	new_collecter = malloc (sizeof (t_cmds));
	if (!new_collecter)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	new_collecter->commands = args.commands;
	new_collecter->redirects = args.redirects;
	return (new_collecter);
}

t_voidlst	*bash_collecter(t_list *head, t_voidlst *myenv)
{
	t_voidlst	*collecter;
	t_cmds	*tmp_list;

	collecter = NULL;
	while (head)
	{
		handle_cmd(&tmp_list, &head, myenv);
		add_back(&collecter, new_node(tmp_list));
		if (head && head->content->token == PIPE)
			head = head->next;
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
			|| head->prev->content->token == S_QUOTE))
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
			printf("\t[%s]\n", mytoken->str);
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

int	main(int ac, char **av, char **env)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;

	head = NULL;
	(void)ac;
	(void)av;
	str = readline("minishell>>: ");
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (0);
	compiler(head);
	head = esc_sp_after_spechar(head);
	//test the collecter of all tokens
	t_voidlst *mylista = bash_collecter(head, take_env(env));
	display_collecter(mylista);
	//test the collecter of all tokens
	return (0);
}
