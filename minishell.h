/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 02:16:18 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/08 10:26:10 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Resources/libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "Resources/parsing.h"
# include "Resources/linked_lst/linked_lst.h"

typedef struct s_exit
{
	int	exit_status;	
	pid_t	pid[1024];
	int		len;
	int		killed;
	int		size;
}t_exit;

t_exit	global_exit;

typedef struct s_env
{
	char	*key;
	char	*value;
}t_env;

typedef struct s_list_env
{
	t_env				data;
	struct s_list_env	*next;
}t_list_env;

typedef struct s_red
{
	char *filetype;
	int type;
}t_red;


typedef struct  s_cmd
{
	char **args;
	t_list redirections;
}t_cmd;


t_list_env	*get_env(char **env);
t_list_env	*get_node_by_key(t_list_env **env, char *key);
t_list_env	*env_dup(t_list_env *env);
t_list_env	*ft_lstnew_node(t_env content);
char		**get_path_value(t_list_env **env);
char		**key_value_of_arg(char *cmd);
char		*get_value_of_key(t_list_env **env, char *key);
char		*ft_strjoin_export(char const *s1, char const *s2);
void		print_env(t_list_env **env);
void		set_value_of_key(t_list_env **env, char *key, char *value);
void		execute(t_list_env **new_env, char **cmd_parsed);
int			ft_cd(t_list_env **env, char **cmd);
int			ft_pwd(void);
void		ft_exit(char **cmd);
int			ft_echo(char **cmd);
int			ft_env(t_list_env **env);
void		ft_unset(t_list_env **env, char *key);
int			builtin_functions(t_list_env **new_env,
				t_list_env **export_list, char **cmd_parsed);
int			ft_export(t_list_env **env, t_list_env **export_list, char **cmd);
void		free_node(t_list_env *node);
void		free_env(t_list_env *env);
void		add_back_to_list(t_list_env **lst, t_list_env *new);
void		sort_list(t_list_env *list);
void		print_env_export(t_list_env **env);
void		export_valid(t_list_env **env, t_list_env **export_list, char *cmd);
void		export_equ_only(t_list_env **env,
				t_list_env **export_list, char *cmd);
void		export_join(t_list_env **env, t_list_env **export_list, char *cmd);
void		add_to_export_only(t_list_env **export_list, char *cmd);
int			is_builtin(char **cmd_parsed);
int			env_size(t_list_env *env);
int			check_equal_existance(char *cmd1);
int			ft_strcmp(char *s1, char *s2);
int			check_plus_existance(char *cmd);
int			check_key_value_isvalid_export(char *cmd);
void		ft_pipe(t_list_env **m_export, t_voidlst *commands, t_list_env **new_env);
void		exit_status(int status);
void		ft_kill(t_exit *glob);
void		execute_commands(char **cmds, t_list_env **new_env, t_list_env **m_export);
void		redirections(t_voidlst *commands, t_voidlst *red, t_list_env **m_export, t_list_env **new_env);

#endif