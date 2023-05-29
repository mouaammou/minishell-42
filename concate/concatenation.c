/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:45:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/29 21:13:06 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_list	*concatenate_strings(t_list *tokenizer)
{
	char	*join;
	int		flag;
	t_list	*newlist;
	t_list	*tmp_list;
	int		token;
	
	newlist = NULL;
	tmp_list = tokenizer;
	while (tokenizer)
	{
		join = NULL;
		flag = 0;
		while (tokenizer && is_word(tokenizer->content->token) && tokenizer->next && is_word (tokenizer->next->content->token))
		{
			join = ft_strjoin(join, tokenizer->content->str);
			tokenizer = tokenizer->next;
			flag = 1;
		}
		if (is_word (tokenizer->content->token) && flag)
			join = ft_strjoin(join, tokenizer->content->str);
		if (join)
		{
			if (ft_strchr(join, '$'))
				token = DLR;
			else
				token = WORD;
			ft_lstadd_back(&newlist, ft_lstnew(new_token(join, token)));
		}
		else if (tokenizer)
			ft_lstadd_back(&newlist, ft_lstnew(new_token(tokenizer->content->str, tokenizer->content->token)));
		if (!tokenizer)
			break;
		free(join);
		tokenizer = tokenizer->next;
	}
	return (free_linked_list(tmp_list), newlist);
}

// int	main(int ac, char **av)
// {
// 	t_list	*head;
// 	char	*str;
// 	char	*trimed_str;
// 	t_list	*newhead;

// 	head = NULL;
// 	(void)ac;
// 	(void)av;
// 	str = readline("minishell>>: ");
// 	// add_history(str);
// 	if (!str)
// 		return (0);
// 	trimed_str = ft_strtrim(str, " ");
// 	if (!give_tokens(&head, trimed_str, 0))
// 		return (myfree_func(head, trimed_str, str), 11);
// 	if (!compiler(head))
// 		return (myfree_func(head, trimed_str, str), 12);
// 	newhead = esc_sp_after_spechar(head);
// 	newhead = token_dbquotes(newhead);
// 	newhead = concatenate_strings(newhead);
// 	affiche(newhead);
// 	exit (0);

// 	/* I have to concatenate here */
// 	return (0);
// }

