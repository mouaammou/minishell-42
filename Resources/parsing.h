/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/04 17:20:44 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define  PARSING_H

# include <stdio.h>
# include <fcntl.h>
# include "linked_lst/linked_lst.h" // here all the structs used in this project
# include <readline/readline.h>
# include <readline/history.h>
# include "new_linkedlist/list.h"
# include "compiler/compiler.h"
# include "tokenizer/tokenizer.h"
# include "utils/utils.h"
# include "expander/expander.h"
# include "concate/concate.h"
# include "parsing/parser.h"
# include "libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define PREV 0
# define NEXT 1
# define BOTH 2

#endif
