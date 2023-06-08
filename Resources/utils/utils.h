/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:24:03 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 00:28:30 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

int	check_token(t_list *node, int mytoken1, int mytoken2, int flag);
int	check_pipe(t_list *node);
int	syntax_error(char *str, char *token_value);
int	check_syntax(t_list *newlist);

t_token	*get_quotes_content(char *str, int *i, char qts);
int	token_quotes(t_list **mylist, char *str, int *i, int token);
int	tokeni_mychar(t_list **mylist, char *str, int *i, int value);
int	spechars_pase_1(t_list **mylist, char *str, int *i);
int	spechars_pase_2(t_list **mylist, char *str, int *i);

char	*token_word(char *str, int *i, int start);
char	*token_var(char *str, int *i, int start);
int	set_token_word(t_list **mylist, int *i, char *str);
int	set_token_var(t_list **mylist, int *i, char *str);
int	token_spechars(t_list **mylist, char *str, int *i);

void	*msg_error(char *str);
int	myfree_func(t_list *head, char *trimed_str, char *str);
void	free_linked_list(t_list *head);
void	free_nodes(t_list *head);

#endif
