/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/10 00:53:39 by mouaammo         ###   ########.fr       */
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
# include "gnl/get_next_line.h"
# include "new_linkedlist/list.h"
# include "compiler/compiler.h"
# include "tokenizer/tokenizer.h"
# include "utils/utils.h"
# include "expander/expander.h"
# include "concate/concate.h"
# include "parsing/parser.h"

# define PREV 0
# define NEXT 1
# define BOTH 2

int	g_exit_status;

#endif
