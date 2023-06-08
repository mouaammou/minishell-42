/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:32:29 by drtaili           #+#    #+#             */
/*   Updated: 2023/05/31 03:48:45 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_get_back_again(t_list_env **env)
{
	if (chdir(get_value_of_key(env, "OLDPWD")) == -1)
	{
		perror("chdir");
	}
	else
	{
		set_value_of_key(env, "OLDPWD", get_value_of_key(env, "PWD"));
		set_value_of_key(env, "PWD", get_value_of_key(env, "OLDPWD"));
		return (0);
	}
	return (1);
}

int	cd_to_path(t_list_env **env, char **cmd)
{
	char	*new_path;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	new_path = ft_strjoin("/", cmd[1]);
	new_path = ft_strjoin(cwd, new_path);
	if (chdir(new_path) == -1)
		perror("chdir");
	else
	{
		set_value_of_key(env, "OLDPWD", get_value_of_key(env, "PWD"));
		set_value_of_key(env, "PWD", new_path);
		return (0);
	}
	return (1);
}

int	ft_cd(t_list_env **env, char **cmd)
{
	if (!ft_strcmp(cmd[1], "-"))
	{
		return (ft_cd_get_back_again(env));
	}
	else
	{
		return (cd_to_path(env, cmd));
	}
}
