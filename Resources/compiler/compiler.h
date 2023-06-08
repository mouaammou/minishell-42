/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:23:01 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 00:31:45 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPILER_H
#define	COMPILER_H

int		is_word(int token);
int		is_spechar(int token);
t_list	*ighnore_space(t_list *head);
t_list	*compiler(t_list *head);

#endif
