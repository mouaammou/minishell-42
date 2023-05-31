/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collecter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:25:24 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/31 19:12:59 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTER_H
# define  COLLECTER_H

# include "../parsing.h"

typedef struct cmd
{
	t_voidlst	*commands;
	t_voidlst	*redirects;
}t_cmds;

typedef struct s_env
{
	char	*key;
	char	*value;
}t_env;

//command.c
void		add_multi_nodes(t_voidlst **origin, t_voidlst *newlist);
void		handle_cmd(t_cmds **tmp_list, t_list **head, t_voidlst *myenv);
t_cmds		*node_collecter(t_cmds args);
t_voidlst	*bash_collecter(t_list *tokenizer, t_voidlst *myenv);

//expander.c
void		command_expansion(t_voidlst **origin, t_list **head,
				t_voidlst *myenv, int flag);
void		expand_qts_mark(t_voidlst **origin, t_list **head);
// t_voidlst	*expander(t_list *head, t_voidlst *myenv);

//heredoc.c
void		manage_heredoc(t_list **head, int *fd);
void		handle_heredoc(t_list **head);

//token_db_quotes.c
t_list		*token_dbquotes(t_list *tokenizer);

//utils1.c
t_env		*split_key_value(char *env);
void		free_all(char **tab);
t_voidlst	*take_env(char **env);
char		*search_for_key(char *str, t_voidlst *myenv);
void		ft_error(char *error, int error_val);

//utils2.c
t_token		*new_token(char *str, int token);
t_voidlst	*new_sublist(char **split, int token);
int			index_of_char(char *str, char c);
int			str_cmp(const char *s1, const char *s2);
t_list		*esc_sp_after_spechar(t_list *head);
#endif
