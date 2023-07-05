/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/05 14:06:38 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include "../../minishell.h"

void	concate_in_heredoc(t_list **head, int *flag, char **delemiter)
{
	*flag = 0;
	*delemiter = NULL;
	(*head) = (*head)->next;
	while ((*head) && (*head)->content->token != ESP
		&& !is_redirect((*head)->content->token)
		&& (*head)->content->token != PIPE)
	{
		if ((*head)->content->token == QUOTE
			|| (*head)->content->token == S_QUOTE)
			*flag = 1;
		*delemiter = ft_strjoin_1(*delemiter, ft_strdup((*head)->content->str));
		(*head) = (*head)->next;
	}
	*delemiter = ft_strjoin_1(*delemiter, ft_strdup("\n"));
}

void	manage_heredoc(t_list **head, int *fd, t_list_env *myenv)
{
	char	*delemiter;
	char	*line;
	char	*buffer;
	int		flag;

	buffer = NULL;
	concate_in_heredoc(head, &flag, &delemiter);
	while (g_global_exit.flag)
	{
		line = readline("heredoc> ");
		if (line)
			line = ft_strjoin_1(line, ft_strdup("\n"));
		if (!line || !str_cmp(line, delemiter))
		{
			free(delemiter);
			if (buffer)
				write(*fd, buffer, ft_strlen(buffer));
			free(line);
			free(buffer);
			break ;
		}
		if (ft_strchr(line, '$') && !flag)
			line = replace_all(line, myenv);
		buffer = ft_strjoin_1(buffer, line);
	}
}

int	handle_heredoc(t_list **newlist, t_list **head, t_list_env *myenv)
{
	char		*str;
	int			fd;
	char		*int_str;
	static int	i;

	g_global_exit.heredoc = 1;
	int_str = ft_itoa(i++);
	str = ft_strjoin_1(ft_strdup("/tmp/file"), int_str);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_printf(2, "minishell: bad file descriptor\n");
		return (0);
	}
	manage_heredoc(head, &fd, myenv);
	close (fd);
	ft_lstadd_back(newlist, ft_lstnew(new_token(str, RE_IN)));
	free(str);
	g_global_exit.heredoc = 0;
	return (1);
}
