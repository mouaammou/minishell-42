/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:24:31 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/25 00:04:59 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	look_for_key(char *str, t_list_env **env)
{
	t_list_env	*ev;

	ev = *env;
	while (ev)
	{
		if (ft_strcmp(str, ev->data.key) == 0)
			return (0);
		ev = ev->next;
	}
	return (1);
}

int	cd_only(t_list_env **env)
{
	if (look_for_key("HOME", env))
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		return (0);
	}
	else if (!look_for_key("HOME", env)
		&& !ft_strcmp(get_value_of_key(env, "HOME"), "\0"))
	{
		return (0);
	}
	else if (chdir(get_value_of_key(env, "HOME")) == -1)
		perror("minishell");
	return (1);
}

void	build_new_oldpwd_pwd(t_list_env **env)
{
	t_env		content1;
	t_env		content2;
	char		cwd[1024];
	t_list_env	*new1;
	t_list_env	*new2;
	char		*pwd;

	if (look_for_key("PWD", env))
	{
		content1.key = ft_strdup("PWD");
		content1.value = ft_strdup(getcwd(cwd, sizeof(cwd)));
		new1 = ft_lstnew_node(content1);
		if (content1.key)
			free(content1.key);
		if (content1.value)
			free(content1.value);
		add_back_to_list(env, new1);
	}
	else
	{
		pwd = get_value_of_key(env, ft_strdup("PWD"));
		if (look_for_key("OLDPWD", env))
		{
			puts("here");
			content2.key = ft_strdup("OLDPWD");
			content2.value = ft_strdup(pwd);
			new2 = ft_lstnew_node(content2);
			if (content2.key)
				free(content2.key);
			if (content2.value)
				free(content2.value);
			add_back_to_list(env, new2);
		}
	}
}
