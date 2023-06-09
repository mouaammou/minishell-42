/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:39:05 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/09 17:40:27 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_and_reset(t_voidlst *mycommands)
{
	t_voidlst	*tmp_next;
	t_command	*my_args;

	while (mycommands)
	{
		tmp_next = mycommands->next;
		my_args = mycommands->content;
		free_all(my_args->args);
		free_voidlst(my_args->redirections);
		free(mycommands);
		mycommands = tmp_next;
	}
}

t_voidlst	*tokenizer_and_grammar(char	*str, t_list *head, t_voidlst *myenv)
{
	char		*trimed_str;
	t_list		*expander_list;

	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (myfree_func(head, trimed_str, str), NULL);
	if (!compiler(head))
		return (myfree_func(head, trimed_str, str), NULL);
	free(trimed_str);
	free(str);
	head = esc_sp_after_spechar(head);
	expander_list = bash_expander(head, myenv);
	return (bash_concate(expander_list));
}
