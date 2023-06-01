/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/01 16:37:38 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*delete_last_char(char* str) {
    int len;
	
	len = ft_strlen(str);
    if (len > 0) {
        str[len-1] = '\0';
    }
	return (str);
}

void	manage_heredoc(t_list **head, int *fd, t_voidlst *myenv)
{
	char	*delemiter;
	char	*line;
	char	*buffer;
	char	*tmpstr;

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
		if (ft_strchr(line, '$') && (tmpstr = delete_last_char(ft_strdup(line))))
		{
			line = search_for_key(tmpstr + 1, myenv);
			line = ft_strjoin(line, ft_strdup("\n"));
			free(tmpstr);
		}
		buffer = ft_strjoin(buffer, line);
	}
	free(delemiter);
	if (buffer)
		write(*fd, buffer, ft_strlen(buffer));
	free(buffer);
}

void	handle_heredoc(t_list **head, t_voidlst *myenv)
{
	char		*str;
	int			fd;
	char		*int_str;
	static		int	i;

	int_str = ft_itoa(i++);
	str = ft_strjoin(ft_strdup("/tmp/file"), int_str);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_error("bad file descriptor\n", 3);
	manage_heredoc(head, &fd, myenv);
	free((*head)->content->str);
	(*head)->content->token = RE_IN;
	(*head)->content->str = str;
	close (fd);
}
