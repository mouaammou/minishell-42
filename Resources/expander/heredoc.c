/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 02:24:19 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	concate_in_heredoc(t_list **head, int *flag, char **delemiter)
{
	*delemiter = NULL;
	(*head) = (*head)->next;
	while ((*head) && (*head)->content->token != ESP
		&& !is_redirect((*head)->content->token))
	{
		if ((*head)->content->token == QUOTE
			|| (*head)->content->token == S_QUOTE)
			*flag = 1;
		*delemiter = ft_strjoin(*delemiter, ft_strdup((*head)->content->str));
		(*head) = (*head)->next;
	}
	*delemiter = ft_strjoin(*delemiter, ft_strdup("\n"));
}

void	manage_heredoc(t_list **head, int *fd, t_voidlst *myenv)
{
	char	*delemiter;
	char	*line;
	char	*buffer;
	int		flag;

	buffer = NULL;
	flag = 0;
	concate_in_heredoc(head, &flag, &delemiter);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line || !str_cmp(line, delemiter))
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		if (ft_strchr(line, '$') && !flag)
			line = replace_all(line, myenv);
		buffer = ft_strjoin(buffer, line);
	}
	free(delemiter);
	if (buffer)
		write(*fd, buffer, ft_strlen(buffer));
	free(buffer);
}

int	handle_heredoc(t_list **newlist, t_list **head, t_voidlst *myenv)
{
	char		*str;
	int			fd;
	char		*int_str;
	static int	i;

	int_str = ft_itoa(i++);
	str = ft_strjoin(ft_strdup("/tmp/file"), int_str);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf("❌❌ bad file descriptor\n");
		return (0);
	}
	manage_heredoc(head, &fd, myenv);
	ft_lstadd_back(newlist, ft_lstnew(new_token(str, RE_IN)));
	close (fd);
	return (1);
}
