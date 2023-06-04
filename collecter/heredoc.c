/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/04 14:15:33 by mouaammo         ###   ########.fr       */
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

char	*join_multi_var(char *str, t_voidlst *myenv)
{
	// char		*searched_str;
	t_list		*db_quote_list;
	char		*join;
	myenv = NULL;
	db_quote_list = NULL;
	give_tokens(&db_quote_list, str, 0);
	
	join = NULL;
	while (db_quote_list)
	{		
		// searched_str = NULL;
		// if (ft_strchr(db_quote_list->content->str, '$'))
		// 	searched_str = search_for_key(db_quote_list->content->str + 1, myenv);
		// if (searched_str)
		// 	db_quote_list->content->str = searched_str;
		// else if (ft_strchr(db_quote_list->content->str, '$')
		// 	&& !manage_others(db_quote_list->content->str))
		// 	db_quote_list->content->str = NULL;
		// if (db_quote_list->content->str)
		// 	join = ft_strjoin(join, db_quote_list->content->str);
		// printf("new string :[%s]\n", ft_strtrim(db_quote_list->content->str, ft_strdup("'")));
		printf("str: [%s] -- token: %d\n", db_quote_list->content->str, db_quote_list->content->token);
		db_quote_list = db_quote_list->next;
	}
	printf("join : %s\n", join);
	return (join);
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
			line = join_multi_var(tmpstr, myenv);
			if (line)
				line = ft_strjoin(line, ft_strdup("\n"));
			free(tmpstr);
		}
		buffer = ft_strjoin(buffer, line);
	}
	free(delemiter);
	if (buffer)
		write(*fd, buffer, ft_strlen(buffer));
	free(buffer);
	// exit (0);
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
