/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/31 21:36:20 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	manage_heredoc(t_list **head, int *fd)
{
	char	*delemiter;
	char	*line;
	char	*buffer;

	buffer = NULL;
	delemiter = ft_strjoin((*head)->next->content->str, ft_strdup("\n"));
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line || !str_cmp(line, delemiter))
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		buffer = ft_strjoin(buffer, line);
		free(line);
	}
	free(delemiter);
	if (buffer)
		write(*fd, buffer, ft_strlen(buffer));
}

void	handle_heredoc(t_list **head)
{
	char		*str;
	int			fd;
	char		*int_str;
	static		int	i;

	int_str = ft_itoa(i++);
	str = ft_strjoin("/tmp/file", int_str);
	free(int_str);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_error("bad file descriptor\n", 3);
	manage_heredoc(head, &fd);
	free((*head)->content->str);
	(*head)->content->token = RE_IN;
	(*head)->content->str = str;
	close (fd);
}
