/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 08:35:43 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/17 18:18:03 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// ./minishell < nn.txt sort > out.txt
// 0			1 2		 3	  4	5		| ac = 6 | ac - 2 = 4

void	red_output(t_voidlst *commands, t_voidlst *red, t_list_env **m_export, t_list_env **new_env)
{
	int	store_fd;
	int fd_out = open(((t_token *)red->content)->str, O_WRONLY | O_CREAT | O_TRUNC, 0666); // 0666 the 0 means that this is in octal
	if (fd_out == -1)
	{
		// perror("minishell");
		ft_printf(2, "minishell: ambiguous redirect\n");
		return;
	}
	store_fd = dup(1);
	dup2(fd_out, 1);
	redirections(commands, red->next, m_export, new_env);
	dup2(store_fd, 1);
	close(fd_out);
}
void	red_input(t_voidlst *commands, t_voidlst *red, t_list_env **m_export, t_list_env **new_env)
{
	int	store_fd;	
	int fd_in = open(((t_token *)red->content)->str, O_RDONLY, 0644);//str howa input file mnin anqraw
	if (fd_in == -1)
	{
		ft_printf(2, "minishell: ambiguous redirect\n");
		return;
	}
	store_fd = dup(0);
	dup2(fd_in, 0);
	redirections(commands, red->next, m_export, new_env);
	dup2(store_fd, 0);
	close(fd_in);
}

void	red_double_output(t_voidlst *commands, t_voidlst *red, t_list_env **m_export, t_list_env **new_env)
{
	int store_fd;
	int d_fd_out = open(((t_token *)red->content)->str, O_WRONLY | O_CREAT |  O_APPEND, 0666);
	if (d_fd_out == -1)
	{
		ft_printf(2, "minishell: ambiguous redirect\n");
		return;
	}
	store_fd = dup(1);
	dup2(d_fd_out, 1);
	redirections(commands, red->next, m_export, new_env);
	dup2(store_fd, 1);
	close(d_fd_out);
}

void	red_double_input(t_voidlst *commands, t_voidlst *red, t_list_env **m_export, t_list_env **new_env)
{
	int store_fd;
	int fd[2];
	pipe(fd);
	store_fd = dup(0);
	ft_putstr_fd(((t_token *)red->content)->str, fd[1]);
	close(fd[1]);
	dup2(fd[0], 0);
	redirections(commands, red->next, m_export, new_env);
	dup2(store_fd, 0);
	close(fd[0]);
}

int	redirections(t_voidlst *commands, t_voidlst *red, t_list_env **m_export, t_list_env **new_env)
{
	if (red == NULL && ((t_command *)(t_voidlst *)commands->content)->args[0])
		execute_commands(((t_command *)(t_voidlst *)commands->content)->args, new_env, m_export);
	else if (red && ((t_token *)red->content)->token == RE_OUT)//>
		red_output(commands, red, m_export, new_env);
	else if (red && ((t_token *)red->content)->token == RE_IN)//<
		red_input(commands, red, m_export, new_env);
	else if (red && ((t_token *)red->content)->token == RE_APPEND)//>>
		red_double_output(commands, red, m_export, new_env);
	else if (red && ((t_token *)red->content)->token == HERE_DOC)//<<
		red_double_input(commands, red, m_export, new_env);
	return (g_global_exit.exit_status);
}
