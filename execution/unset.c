/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:45:35 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/22 22:27:50 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_list_env **env, char *key)
{
	t_list_env	*prev;
	t_list_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->data.key, key) == 0)
		{
			if (prev == NULL)
			{
				*env = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}
			free_node(curr);
			g_global_exit.exit_status = 0;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	g_global_exit.exit_status = 1;
}

int	wrongkey(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '+' || cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	handle_err(char *cmd)
{
	int	err;

	err = 0;
	if (wrongkey(cmd))
	{
		ft_printf(2, "minishell : unset: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	else if (cmd[0] == '-')
	{
		ft_printf(2, "minishell : unset: invalid option\n");
		return (2);
	}
	else if (cmd[0] == '!')
	{
		ft_printf(2, "minishell : unset: event not found\n");
		return (2);
	}
	else
	{
		ft_printf(2, "minishell : unset: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	return (-1);
}

int	unset_some(t_list_env **env, t_list_env **export_list, char **cmd, int len)
{
	int	i;
	int	err;
	int	chk;

	i = 1;
	err = 0;
	chk = 0;
	while (i < len)
	{
		if (check_key_value_isvalid_export(cmd[i]))
		{
			ft_unset(env, cmd[i]);
			ft_unset(export_list, cmd[i]);
		}
		else
		{
			err = handle_err(cmd[i]);
			chk = 1;
		}
		i++;
	}
	if (chk == 1)
		return (err);
	return (0);
}

int	main_unset(t_list_env **new_env, t_list_env **export_list, char **cmd)
{
	int	len;
	int	i;
	int	k;
	int	chk;

	chk = 0;
	len = size_cmd(cmd);
	i = 1;
	if (!cmd[1])
		return (0);
	else if (check_export_args(cmd) > 0)
		return (unset_some(new_env, export_list, cmd, len));
	else if ((check_export_args(cmd) == 0))
	{
		if (len == 2)
			return (handle_err(cmd[i]));
		k = 1;
		while (k < len)
		{
			handle_err(cmd[i]);
			k++;
		}
	}
	return (1);
}
