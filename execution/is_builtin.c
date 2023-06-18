/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 05:22:39 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/16 22:42:33 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_functions(t_list_env **new_env,
	t_list_env **export_list, char **cmd_parsed)
{ // TODO: handle redirections
	if (!ft_strcmp(cmd_parsed[0], "exit"))
		ft_exit(cmd_parsed);
	else if (!ft_strcmp(cmd_parsed[0], "cd"))
		return (ft_cd(new_env, cmd_parsed));
	else if (!ft_strcmp(cmd_parsed[0], "pwd"))
		return (ft_pwd(new_env));
	else if (!ft_strcmp(cmd_parsed[0], "echo"))
		return (ft_echo(cmd_parsed));
	else if (!ft_strcmp(cmd_parsed[0], "env"))
	{
		if (!cmd_parsed[1] && !ft_strcmp(get_value_of_key(new_env, "PATH"), "/"))
		{
			// printf("minishell: env: command not found\n");
			ft_putstr_fd("minishell: env: command not found\n", 2);
			return (127);
		}
		else if (!cmd_parsed[1] && get_value_of_key(new_env, "PATH") != NULL)
			return (ft_env(new_env));
		else
		{
			// printf("minishell: env: No such file or directory\n");
			ft_putstr_fd("minishell: env: No such file or directory\n", 2);
			return (127);
		}	
	}
	else if (!ft_strcmp(cmd_parsed[0], "unset"))
	{
		return (main_unset(new_env, export_list, cmd_parsed));
		// ft_unset(new_env, cmd_parsed[1]);
		// ft_unset(export_list, cmd_parsed[1]);
		// if (g_global_exit.exit_status)
		// 	perror("ft_unset");
		// 	// printf("minishell: unset: `%s': not a valid identifier\n", cmd_parsed[1]);
		// return (g_global_exit.exit_status);
	}
	else if (!ft_strcmp(cmd_parsed[0], "export"))
	{
		return (ft_export(new_env, export_list, cmd_parsed));
	}
	return (1);
}

int	is_builtin(char **cmd_parsed)
{
	// if (!cmd_parsed || !(*cmd_parsed))
	// 	return (0);
	if (!ft_strcmp(cmd_parsed[0], "exit") || !ft_strcmp(cmd_parsed[0], "cd")
		|| !ft_strcmp(cmd_parsed[0], "pwd") || !ft_strcmp(cmd_parsed[0], "echo")
		|| !ft_strcmp(cmd_parsed[0], "env")
		|| !ft_strcmp(cmd_parsed[0], "unset")
		|| !ft_strcmp(cmd_parsed[0], "export"))
	{
		return (1);
	}
	return (0);
}
