/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:12:37 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/23 01:59:59 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*env_dup_node(t_env data)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	node->data.key = ft_strdup(data.key);
	node->data.value = ft_strdup(data.value);
	node->next = NULL;
	return (node);
}

t_list_env	*env_dup(t_list_env *env)
{
	t_list_env	*tmp;
	t_list_env	*dup;
	t_list_env	*dup_tail;
	int			i;

	tmp = env;
	dup = NULL;
	i = -1;
	while (++i < env_size(env))
	{
		if (dup == NULL)
		{
			dup = env_dup_node(tmp->data);
			dup_tail = dup;
		}
		else
		{
			dup_tail->next = env_dup_node(tmp->data);
			dup_tail = dup_tail->next;
		}
		tmp = tmp->next;
	}
	return (dup);
}

int	when_key_ends(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	**key_value_of_arg(char *cmd)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	if (check_p_e_existance(cmd))
	{
		tmp[0] = ft_substr(cmd, 0, when_key_ends(cmd) - 1);
		tmp[1] = ft_substr(cmd, when_key_ends(cmd) + 1, ft_strlen(cmd));
		tmp[2] = NULL;
	}
	else if (check_equal_existance(cmd))
	{
		tmp[0] = ft_substr(cmd, 0, when_key_ends(cmd));
		tmp[1] = ft_substr(cmd, when_key_ends(cmd) + 1, ft_strlen(cmd));
		tmp[2] = NULL;
	}
	return (tmp);
}

void	error_exp(char *c)
{
	ft_printf(2, "minishell : export: `%s': not a valid identifier\n", c);
}
