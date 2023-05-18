/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:12:11 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/18 21:38:07 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

void	handle_heredoc(t_list **head, int *i)
{
	char	*str;
	char	*line;

	*i = 0;
	str = ft_strjoin("/tmp/", (*head)->next->content->str);
	int	fd = open(str, O_CREAT | O_RDWR, 777);
	if (fd < 0)
	{
		msg_error("bad file descriptro\n");
		return ;
	}
	// printf("[%s]\n", ft_strjoin((*head)->next->content->str, "\n"));
	// exit (0);
	while ((line = get_next_line(0)))
	{
		write(fd, line, ft_strlen(line));
	}
	// exit (0);
}

void	handle_cmd(t_cmds *cmds, t_list **head, int *i)
{
	while ((*head) && (*head)->content->token != PIPE)
	{
		if ((*head)->content->token == WORD || (*head)->content->token == QUOTE
		|| (*head)->content->token == S_QUOTE || (*head)->content->token == ESP)
			ft_lstadd_back(&cmds[*i].commands, ft_lstnew((*head)->content));
		else
		{
			if ((*head)->next)
			{
				if ((*head)->content->token == HERE_DOC)
					handle_heredoc(head, i);
				(*head)->content->str = (*head)->next->content->str;
				ft_lstadd_back(&cmds[*i].redirects, ft_lstnew((*head)->content));
				(*head) = (*head)->next;
			}
		}
		(*head) = (*head)->next;
	}
}

t_cmds	*fill_cmds_redirs(t_cmds *cmds, t_list *head)
{
	int	i;

	i = 0;
	cmds[i].commands = NULL;
	cmds[i].redirects = NULL;
	while (head)
	{
		handle_cmd(cmds, &head, &i);
		i++;
		cmds[i].commands = NULL;
		cmds[i].redirects = NULL;
		if (!head)
			break ;
		if (head->content->token == PIPE)
			head = head->next;
	}
	return (cmds);
}

t_cmds	*bash_parser(t_list *head)
{
	t_cmds	*cmds;
	int		nb_pipes;

	nb_pipes = count_pipes(head);
	if (!nb_pipes)
		return (NULL);
	cmds = malloc(sizeof(t_cmds) * (nb_pipes + 1));
	if (!cmds)
		return (NULL);
	cmds->nb_cmds = nb_pipes;
	cmds = fill_cmds_redirs(cmds, head);
	return (cmds);
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

void	display(t_list *head)
{
	while (head)
	{
		printf("[%s]\n", head->content->str);
		head = head->next;
	}
}

int	main(void)
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
		return (0);
	compiler(head);
	head = esc_sp_after_spechar(head);
	t_cmds *cmds = bash_parser(head);
	t_list *varlist;
	int i = 0;

	while (cmds && i < cmds->nb_cmds)
	{
		varlist = cmds[i].commands;
		printf("command: %d\n", i + 1);
		while (varlist)
		{
			printf("[%s]", varlist->content->str);
			varlist = varlist->next;
		}
		printf("\n");
		i++;
	}
	i = 0;
	while (cmds && i < cmds->nb_cmds)
	{
		varlist = cmds[i].redirects;
		printf("redirect: %d\n", i + 1);
		while (varlist)
		{
			printf("[%s]\t", varlist->content->str);
			printf("token [%d]\t", varlist->content->token);
			varlist = varlist->next;
		}
		printf("\n");
		i++;
	}
	return (0);
}
