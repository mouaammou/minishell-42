/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/20 17:02:36 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define  PARSING_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "linked_lst/linked_lst.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "readline/get_next_line.h"
# include "new_linkedlist/list_header.h"

# define PREV 0
# define NEXT 1
# define BOTH 2

typedef struct s_env
{
	char	*key;
	char	*value;
}t_env;

typedef struct cmds
{
	t_list	*commands;
	t_list	*redirects;
	int		nb_cmds;
}t_cmds;

void	compiler(t_list *head);
int		check_token(t_list *node, int mytoken1, int mytoken2, int flag);
int		syntax_error(char *str, char *token_value);
int		check_syntax(t_list *newlist);
void	free_nodes(t_list *head);
int		give_tokens(t_list **tokenizer, char *str);
t_token	*get_quotes_content(char *str, int *i, char qts);
int		token_quotes(t_list **mylist, char *str, int *i, char qts);
void	tokeni_mychar(t_list **mylist, char *str, int *i, int value);
void	token_spechars(t_list **mylist, char *str, int *i);
int		is_str(char mychar);
void	token_word(t_list **mylist, char *str, int *i);
void	*msg_error(char *str);
int		myfree_func(t_list *head, char *trimed_str, char *str);
void	free_linked_list(t_list *head);

/* start collecter functions */
int		count_pipes(t_list *head);
void	handle_heredoc(t_list **head);
void	handle_cmd(t_cmds *cmds, t_list **head, int *i);
t_cmds	*collect_cmds_redirs(t_cmds *cmds, t_list *head);
t_cmds	*bash_collecter(t_list *head);
t_list *esc_sp_after_spechar(t_list *head);
void	display(t_list *head);
void	display_args(t_cmds *cmds);
void	display_redires(t_cmds *cmds);
void	free_all(char **tab);
/* end collecter */
#endif
