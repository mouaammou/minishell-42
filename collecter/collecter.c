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
					handle_heredoc(head);
				else
					(*head)->content->str = (*head)->next->content->str;
				ft_lstadd_back(&cmds[*i].redirects, ft_lstnew((*head)->content));
				(*head) = (*head)->next;
			}
		}
		(*head) = (*head)->next;
	}
}

t_cmds	*collect_cmds_redirs(t_cmds *cmds, t_list *head)
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

t_cmds	*bash_collecter(t_list *head)
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
	cmds = collect_cmds_redirs(cmds, head);
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
		printf("[%s] ==> [%d]\n", head->content->str, head->content->token);
		head = head->next;
	}
}

void	display_args(t_cmds *cmds)
{
	int i = 0;
	t_list *varlist;

	while (cmds && i < cmds->nb_cmds)
	{
		varlist = cmds[i].commands;
		printf("command: %d\n", i + 1);
		display(varlist);
		i++;
	}
}

void	display_redires(t_cmds *cmds)
{
	int i = 0;
	t_list *varlist;

	while (cmds && i < cmds->nb_cmds)
	{
		varlist = cmds[i].redirects;
		printf("redirect: %d\n", i + 1);
		while (varlist)
		{
			printf("[%s]\ttoken [%d]\n", varlist->content->str, varlist->content->token);
			varlist = varlist->next;
		}
		i++;
	}
}

// int	main(void)
// {
// 	t_list	*head;
// 	char	*str;
// 	char	*trimed_str;

// 	head = NULL;
// 	str = readline("minishell>> :");
// 	if (!str)
// 		return (0);
// 	trimed_str = ft_strtrim(str, " ");
// 	if (!give_tokens(&head, trimed_str))
// 		return (0);
// 	compiler(head);
// 	head = esc_sp_after_spechar(head);
// 	t_cmds *cmds = bash_collecter(head);
// 	display_args(cmds);
// 	printf("------------\n");
// 	display_redires(cmds);
// 	return (0);
// }
