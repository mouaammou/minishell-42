/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:31:57 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/24 01:26:37 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_slash(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	ft_free(char **ret, int k)
{
	int	j;

	j = 0;
	while (j < k)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

char	**env_arr(t_list_env **envr)
{
	t_list_env	*env;
	char		**arr;
	char		*tmp;
	int			i;
	int			len;

	i = 0;
	env = *envr;
	len = env_size(*envr);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	while (env != NULL)
	{
		tmp = ft_strjoin(env->data.key, "=");
		arr[i] = ft_strjoin(tmp, env->data.value);
		if (!arr[i])
			return (ft_free(arr, i), NULL);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	check_value(char **value, char **cmd_parsed)
{
	if (!value)
	{
		ft_printf(2, "minishell : %s: ", cmd_parsed[0]);
		ft_printf(2, "no such file or directory\n");
		g_global_exit.exit_status = 127;
		exit (g_global_exit.exit_status);
	}
	return (0);
}

void	waitforchilds(void)
{
	int	k;

	k = 0;
	while (waitpid(g_global_exit.pid[k++], &g_global_exit.exit_status, 0) != -1)
		;
	if (WIFEXITED(g_global_exit.exit_status))
		WEXITSTATUS(g_global_exit.exit_status);
	g_global_exit.exit_status = g_global_exit.exit_status % 255;
}
