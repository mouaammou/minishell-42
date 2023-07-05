/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 02:16:18 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/24 02:31:38 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "./ft_printf/ft_printf.h"
# include "Resources/parsing.h"

t_list_env	*get_env(char **env);
t_list_env	*get_node_by_key(t_list_env **env, char *key);
t_list_env	*env_dup(t_list_env *env);
t_list_env	*ft_lstnew_node(t_env content);
t_list_env	*build_node(char *key, char *value);
char		**get_path_value(t_list_env **env);
char		**key_value_of_arg(char *cmd);
char		*get_value_of_key(t_list_env **env, char *key);
char		*ft_strjoin_export(char const *s1, char const *s2);
void		print_env(t_list_env **env);
void		set_value_of_key(t_list_env **env, char *key, char *value);
void		execute(t_list_env **new_env, char **cmd_parsed);
int			cd_only(t_list_env **env);
int			look_for_key(char *str, t_list_env **env);
int			ft_cd(t_list_env **env, char **cmd);
int			ft_pwd(t_list_env **env);
void		ft_exit(char **cmd);
int			ft_echo(char **cmd);
int			ft_env(t_list_env **env);
void		ft_unset(t_list_env **env, char *key);
int			builtin_functions(t_list_env **new_env,
				t_list_env **export_list, char **cmd_parsed);
int			ft_export(t_list_env **env, t_list_env **export_list, char **cmd);
void		display_args(t_voidlst *h_list);
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
void		ft_pipe(t_list_env **m_export,
				t_voidlst *commands, t_list_env **new_env);
void		exit_status(int status);
int			ft_kill(t_exit *glob);
void		execute_commands(char **cmds,
				t_list_env **new_env, t_list_env **m_export);
int			redirections(t_voidlst *commands, t_voidlst *red,
				t_list_env **m_export, t_list_env **new_env);
int			size_cmd(char **cmd);
int			main_unset(t_list_env **new_env,
				t_list_env **export_list, char **cmd);
void		handle_interrupt(int sig);
void		exit_status(int status);
char		**env_arr(t_list_env **envr);
void		ft_free(char **ret, int k);
int			check_slash(char *cmd);
int			check_value(char **value, char **cmd_parsed);
void		close_fds(int old_fd_in, int old_fd_out, int i);
void		init_piping(int *fd, int *i);
void		last_command(int old_fd_in, int old_fd_out);
void		in_between_commands(int *fd, int old_fd_in, int old_fd_out);
void		first_command(int *fd);
void		waitforchilds(void);
void		init_glob(t_exit *glob);
void		prompt(void);
void		handle_interrupt(int sig);
void		handler(int sig);
int			ft_kill(t_exit *glob);
void		build_new_oldpwd_pwd(t_list_env **env);
void		free_args(char **args);
void		free_commands(t_voidlst *commands);
void		free_envs(t_list_env *m_export,
				t_voidlst *commands, t_list_env *new_env);
void		free_commands(t_voidlst *commands);
void		free_redirection(t_voidlst *redirections);
void		free_args(char **args);
int			check_export_args(char **cmd);
void		error_exp(char *c);
int			check_p_e_existance(char *cmd);
char		**split_keyvalue(char *env);
int			key_check_without_equ(char *cmd1);
int			check_key_export_with_equ(char *cmd1);

#endif
