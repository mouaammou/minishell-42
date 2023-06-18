/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 04:28:32 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/11 20:12:39 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../parsing.h"

void		free_and_reset(t_voidlst *mycommands);
t_voidlst	*tokenizer_and_grammar(char	*str, t_list *head, t_list_env *myenv);
t_command	*allocate_and_fill(t_voidlst	*cmds);
int			fill_command(t_voidlst *cmds, t_voidlst *redirs,
				t_voidlst **new_list);
t_voidlst	*parse_to_args(t_voidlst *h_list);

#endif
