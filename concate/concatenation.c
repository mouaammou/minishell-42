/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:45:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/29 19:38:39 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_list	*concatenate_strings(t_list *tokenizer)
{
	char	*join;
	t_list	*newlist;
	int		flag;
	
	newlist = NULL;
	while (tokenizer)
	{
		join = NULL;
		flag = 0;
		while (tokenizer && tokenizer->content->token != ESP && tokenizer->next && tokenizer->next->content->token != ESP)
		{
			join = ft_strjoin(join, tokenizer->content->str);
			tokenizer = tokenizer->next;
			flag = 1;
		}
		if (tokenizer->content->token != ESP && flag)
			join = ft_strjoin(join, tokenizer->content->str);
		if (join)
			ft_lstadd_back(&newlist, ft_lstnew(new_token(join, WORD)));
		else if (tokenizer)
			ft_lstadd_back(&newlist, ft_lstnew(new_token(tokenizer->content->str, tokenizer->content->token)));
		if (!tokenizer)
			break;
		free(join);
		tokenizer = tokenizer->next;
	}
	return (newlist);
}

int	main(int ac, char **av)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;
	t_list	*newhead;

	head = NULL;
	(void)ac;
	(void)av;
	str = readline("minishell>>: ");
	// add_history(str);
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str, 0))
		return (myfree_func(head, trimed_str, str), 11);
	if (!compiler(head))
		return (myfree_func(head, trimed_str, str), 12);
	newhead = esc_sp_after_spechar(head);
	newhead = token_dbquotes(newhead);
	newhead = concatenate_strings(newhead);
	affiche(newhead);
	exit (0);

	/* I have to concatenate here */
	return (0);
}

