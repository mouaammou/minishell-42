/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/12 17:13:12 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system ("leaks minishell");
}

int	main(void)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;

	atexit(leaks);
	head = NULL;
	str = readline("minishell>> :");
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (myfree_func(head, trimed_str, str), 1);
	return (myfree_func(head, trimed_str, str));
}
