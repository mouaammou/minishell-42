/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/26 18:44:21 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	manage_heredoc(t_list **head, int *fd)
{
	char	*tmp;
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		tmp = ft_strjoin((*head)->next->content->str, "\n");
		if (!line || !str_cmp(line, tmp))
		{
			ft_putstr_fd("\n", 1);
			break ;
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
