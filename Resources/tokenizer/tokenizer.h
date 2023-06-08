/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:32:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 00:39:10 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

int	give_tokens(t_list **tokenizer, char *str);
int	token_db_dollar(t_list **mylist, int *i, int token);
int	token_qts_mark(t_list **mylist, int *i, int token);
int	myspechars(char c);
int	tokens_part_1(t_list **tokenizer, char *str, int *i);
int	tokens_part_2(t_list **tokenizer, char *str, int *i);

#endif
