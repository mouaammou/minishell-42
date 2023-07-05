/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:26:49 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/22 22:29:00 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_args(char **cmd)
{
	int	i;
	int	tmp;
	int	len;

	len = size_cmd(cmd);
	tmp = 0;
	i = 1;
	while (i < len)
	{
		if (check_key_value_isvalid_export(cmd[i]))
			tmp++;
		i++;
	}
	return (tmp);
}

int	export_some(t_list_env **env, t_list_env **export_list, char **cmd, int len)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (i < len)
	{
		if (check_key_value_isvalid_export(cmd[i]))
			export_valid(env, export_list, cmd[i]);
		else
		{
			error_exp(cmd[i]);
			err = 1;
		}
		i++;
	}
	if (err != 0)
		return (1);
	return (0);
}

void	all_args_not_valid(int len, char **cmd)
{
	int	i;

	i = 1;
	while (i < len)
	{
		error_exp(cmd[i]);
		i++;
	}
}

void	build_path(t_list_env **env)
{
	t_env		content;
	t_list_env	*new;

	if (look_for_key("PATH", env))
	{
		content.key = "PATH";
		content.value = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
		new = ft_lstnew_node(content);
		add_back_to_list(env, new);
	}
}

int	ft_export(t_list_env **env, t_list_env **export_list, char **cmd)
{
	int	err;
	int	len;

	len = size_cmd(cmd);
	err = 0;
	if (!cmd[1])
	{
		sort_list(*export_list);
		print_env_export(export_list);
		return (0);
	}
	else if (check_export_args(cmd) > 0)
		return (export_some(env, export_list, cmd, len));
	else if ((check_export_args(cmd) == 0))
		all_args_not_valid(len, cmd);
	return (1);
}
