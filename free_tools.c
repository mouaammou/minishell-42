/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:28:08 by drtaili           #+#    #+#             */
/*   Updated: 2023/07/04 14:16:08 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args && !args[0])
		return ;
	while (args && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_redirection(t_voidlst *redirections)
{
	t_voidlst	*tmp;
	t_token		*my_red;

	tmp = redirections;
	while (redirections)
	{
		tmp = redirections->next;
		my_red = redirections->content;
		free(my_red->str);
		free(my_red);
		free(redirections);
		redirections = tmp;
	}
}

void	free_commands(t_voidlst *commands)
{
	t_voidlst	*tmp;
	t_command	*mycommand;

	while (commands)
	{
		tmp = commands->next;
		mycommand = commands->content;
		free_args(mycommand->args);
		free_redirection(mycommand->redirections);
		free(mycommand);
		free(commands);
		commands = tmp;
	}
}

void	free_envs(t_list_env *m_export,
	t_voidlst *commands, t_list_env *new_env)
{
	commands = NULL;
	free_commands(commands);
	free_env(m_export);
	free_env(new_env);
}
