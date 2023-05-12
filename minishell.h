/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/12 17:15:41 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define  MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include "linked_lst/linked_lst.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum tokens
{
	QUOTE = 1,
	S_QUOTE = 2,
	WORD = 3,
	PIPE = 4,
	RE_OUT = 5,
	RE_IN = 6,
	RE_OUT_A = 7,
	HERE_DOC = 8,
	ESP = 9,
}	t_token;

typedef struct token
{
	char		*str;
	t_token		token;
}t_token;

int		give_tokens(t_list **tokenizer, char *str);
t_token	*get_quotes_content(char *str, int *i, char qts);
int		token_quotes(t_list **mylist, char *str, int *i, char qts);
void	tokeni_mychar(t_list **mylist, int *i, int value);
void	token_spechars(t_list **mylist, char *str, int *i);
int		is_str(char mychar);
void	token_word(t_list **mylist, char *str, int *i);
void	*msg_error(char *str);
int		myfree_func(t_list *head, char *trimed_str, char *str);
void	free_linked_list(t_list *head);
#endif
