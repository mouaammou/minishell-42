/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:11:16 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/25 00:06:19 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_get_back_again(t_list_env **env)
{
	char	cwd[1024];

	if (look_for_key("OLDPWD", env))
	{
		ft_printf(2, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	else if (chdir(get_value_of_key(env, "OLDPWD")) == -1)
	{
		perror("minishell: cd");
	}
	else
	{
		if (look_for_key("PWD", env))
			build_new_oldpwd_pwd(env);
		else if (!look_for_key("PWD", env) && look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			set_value_of_key(env, "OLDPWD", get_value_of_key(env, "PWD"));
			set_value_of_key(env, "PWD", getcwd(cwd, sizeof(cwd)));
		}
		return (0);
	}
	return (1);
}

int	ft_cd_to_home(t_list_env **env)
{
	if (look_for_key("HOME", env))
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		return (1);
	}
	else if (chdir(get_value_of_key(env, "HOME")) == -1)
	{
		perror("minishell: cd");
	}
	else
	{
		if (look_for_key("PWD", env))
			build_new_oldpwd_pwd(env);
		else if (!look_for_key("PWD", env) && look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			set_value_of_key(env, "OLDPWD", get_value_of_key(env, "PWD"));
			set_value_of_key(env, "PWD", get_value_of_key(env, "HOME"));
		}
		return (0);
	}
	return (1);
}

int	cd_to_relative_path(t_list_env **env, char **cmd)
{
	char	*new_path;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	new_path = ft_strjoin_1(ft_strdup("/"), ft_strdup(cmd[1]));
	new_path = ft_strjoin_1(ft_strdup(cwd), new_path);
	if (chdir(new_path) == -1)
		perror("minishell: cd");
	else
	{
		if (look_for_key("PWD", env))
			build_new_oldpwd_pwd(env);
		else if (!look_for_key("PWD", env) && look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			puts("2");
			set_value_of_key(env, "OLDPWD", get_value_of_key(env, "PWD"));
			set_value_of_key(env, "PWD", new_path);
		}
		free(new_path);
		return (0);
	}
	free(new_path);
	return (1);
}

int	cd_to_absolute_path(t_list_env **env, char **cmd)
{
	if (chdir(cmd[1]) == -1)
		perror("minishell: cd");
	else
	{
		if (look_for_key("PWD", env))
			build_new_oldpwd_pwd(env);
		else if (!look_for_key("PWD", env) && look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			set_value_of_key(env, "OLDPWD", get_value_of_key(env, "PWD"));
			set_value_of_key(env, "PWD", cmd[1]);
		}
		return (0);
	}
	return (1);
}

int	ft_cd(t_list_env **env, char **cmd)
{
	char	cwd[1024];

	if (!cmd[1])
		return (cd_only(env));
	else if (!ft_strcmp(cmd[1], "-") || !ft_strcmp(cmd[1], "~"))
	{
		if (!ft_strcmp(cmd[1], "~"))
			return (ft_cd_to_home(env));
		return (ft_cd_get_back_again(env));
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			ft_printf(2, "minishell: cd: error retrieving current directory:"\
			"getcwd: cannot access parent directories:"\
			"No such file or directory\n");
			return (ft_cd_to_home(env));
		}
		else if (cmd[1][0] == '/')
			return (cd_to_absolute_path(env, cmd));
		else
			return (cd_to_relative_path(env, cmd));
	}
	return (0);
}
