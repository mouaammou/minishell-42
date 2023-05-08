/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/08 21:48:17 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	display_tokens (t_list *head)
{
	int i = 0;
	while (head)
	{
		t_token *ftoken = (t_token *) head->content;
		printf("%s\n", ftoken->str);
		printf("%d\n", ftoken->token);
		head = head->next;
	}
}

char	**join_args(int ac, char **av)
{
	char	*str;
	char	**split;
	str = readline("minishell >>: ");
	split = ft_split(str, ' ');
	return (split);
}

void	analyse_tokens(t_token *mytoken)
{
	char	*str;
	int		i;

	i = 0;
	str = mytoken->str;
}

void	give_tokens(t_list *head)
{
	t_token	*mytoken;

	while (head)
	{
		mytoken = (t_token *) head->content;
		analyse_tokens(mytoken);
		head = head->next;
	}
}

int main (int ac, char **av)
{
	int i = 0;
	t_list *head = NULL;
	char **split = join_args(ac, av);
	while (split[i])
	{
		t_token *data = malloc (sizeof (t_token));
		if (!data)
			return (1);
		data->str = split[i];
		data->token = i + 1;
		ft_lstadd_back(&head, ft_lstnew(data));
		i++;
	}
	give_tokens(head);
	display_tokens(head);
	return (0);
}
