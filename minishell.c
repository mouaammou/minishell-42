/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/10 15:13:37 by mouaammo         ###   ########.fr       */
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
		if (ftoken->token  == WORD)
			puts("word");
		if (ftoken->token  == PIPE)
			puts("PIPE");
		if (ftoken->token  == RE_OUT)
			puts("RE OUTPUT");
		if (ftoken->token  == RE_IN)
			puts("RE INPUT");
		if (ftoken->token  == HERE_DOC)
			puts("HERE_DOC");
		if (ftoken->token  == RE_OUT_A)
			puts("RE_OUT_A");
		head = head->next;
	}
}

int	is_str(char mychar)
{
	if (mychar != '|' && mychar != '<' && mychar != '>'
		&& mychar != '\'' && mychar != '\"' && mychar != ' ')
		return (1);
	return (0);
}

int	search_index (char *str, char a)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return (i);
		i++;
	}
	return (i);
}

void	token_word(t_list **mylist, char *str, int *i)
{
	int		j;
	int		start;
	t_token	*mytoken;

	j = 0;
	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	while (str[*i] && is_str(str[*i]))
	{
		(*i)++;
		j++;
	}
	mytoken->str = ft_substr(str, start, j);
	mytoken->token = WORD;
	ft_lstadd_back(mylist, ft_lstnew(mytoken));
}

void	token_quotes(t_list **mylist, char *str, int *i, char qts)
{
	int		j;
	int		start;

	(*i)++;
	j = 0;
	start = *i;
	t_token	*mytoken;
	mytoken = malloc (sizeof (t_token));
	while (str[*i] && str[*i] != qts)
	{
		(*i)++;
		j++;
	}

	mytoken->str = ft_substr(str, start, j);
	mytoken->token = QUOTE;
	ft_lstadd_back(mylist, ft_lstnew(mytoken));
}

void	tokeni_mychar(t_token *mytoken, int *i, int value)
{
	mytoken->token = value;
	(*i)++;
}

void	token_spechars(t_list **mylist, char *str, int *i)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	mytoken->str = NULL;
	if (str[*i] == '|')
		tokeni_mychar(mytoken, i, PIPE);
	else if (str[*i] == ' ')
		tokeni_mychar(mytoken, i, ESP);
	else if (str[*i] == '<' && str[(*i) + 1] == '<')
	{
		(*i)++;
		tokeni_mychar(mytoken, i, HERE_DOC);
	}
	else if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		(*i)++;
		tokeni_mychar(mytoken, i, RE_OUT_A);
	}
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
		tokeni_mychar(mytoken, i, RE_IN);
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
		tokeni_mychar(mytoken, i, RE_OUT);
	ft_lstadd_back(mylist, ft_lstnew(mytoken));
}


void	give_tokens(t_list **tokenizer, char *str)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	while (str[i])
	{
		if (is_str(str[i]))
			token_word(tokenizer, str, &i);
		if (str[i] == '\'')
			token_quotes(tokenizer, str, &i, '\'');
		if (str[i] == '\"')
			token_quotes(tokenizer, str, &i, '\"');
		if (!is_str(str[i]))
			token_spechars(tokenizer, str, &i);
	}
}

void	analyse_str(t_list **tokenizer, char *str)
{
	char	*one_space;
	char	*trimed_str;

	trimed_str = ft_strtrim(str, " ");
	give_tokens(tokenizer, trimed_str);
}

int main (int ac, char **av)
{
	int		i;
	t_list	*head;
	char	*str;

	head = NULL;
	str = readline("minishell>> :");
	if (!str)
		return (0);
	analyse_str(&head, str);
	display_tokens(head);
	free(str);
	return (0);
}
