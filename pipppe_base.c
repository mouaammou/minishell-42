/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipppe_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:34:02 by drtaili           #+#    #+#             */
/*   Updated: 2023/05/22 17:12:36 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd
{
    char        **args;
    t_commands    *redirects;
}t_cmd;

typedef struct s_commands
{
    t_cmd            *content;
    struct list        *next;
    struct list        *prev;
}    t_commands;

t_list_env	*make_node_cmd(char **my_env)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	if (!node)
		return (NULL);
	node->data.key = my_env[0];
	node->data.value = my_env[1];
	node->next = NULL;
	return (node);
}

t_list_env	*make_list_cmds(int ac, char **av)
{
	t_list_env	*new_env;
	t_list_env	*curr_env;
	t_list_env	*node;
	char		**my_env;
	int			i;

	i = 1;
	new_env = NULL;
	curr_env = NULL;
	while (i < ac)
	{
		my_env = ft_split(av[i], ' ');
		node = make_node_cmd(my_env);
		if (curr_env)
			curr_env->next = node;
		else
			new_env = node;
		curr_env = node;
		i++;
	}
	return (new_env);
}

void	print_env(t_list_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->data.key, env->data.value);
		env = env->next;
	}
}

ls -la => char **cmd => cmd[0] = ls | cmd[1] = -la => argv[1]; 
argv[1] => split b space => char **cmd => make node with fill node with data 

