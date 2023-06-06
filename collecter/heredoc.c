/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/06 17:34:12 by mouaammo         ###   ########.fr       */
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


char*	delete_char(char* str, char c) {
    char* p = ft_strchr(str, c);

    if (p != NULL) {
        ft_memmove(p, p + 1, ft_strlen(p));
    }
    return str;
}

void	manage_heredoc(t_list **head, int *fd, t_voidlst *myenv)
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
		if (ft_strchr(line, '$'))
			line = replace_all(line, myenv);
		buffer = ft_strjoin(buffer, line);
	}
	free(delemiter);
	if (buffer)
		write(*fd, buffer, ft_strlen(buffer));
	free(buffer);
}

int	handle_heredoc(t_list **head, t_voidlst *myenv)
{
	char		*str;
	int			fd;
	char		*int_str;
	static		int	i;

	int_str = ft_itoa(i++);
	str = ft_strjoin(ft_strdup("/tmp/file"), int_str);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf("❌❌ bad file descriptor\n");
		return (0);
	}
	manage_heredoc(head, &fd, myenv);
	free((*head)->content->str);
	ft_lstadd_back(head, ft_lstnew(new_token(str, RE_IN)));
	close (fd);
	// (*head) = (*head)->next;
	return (1);
}
