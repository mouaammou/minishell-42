/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/11 23:35:06 by mouaammo         ###   ########.fr       */
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
		{
			puts("word");
			printf("[%s]\n", ftoken->str);
		}
		if (ftoken->token  == PIPE)
			puts("PIPE");
		if (ftoken->token  == RE_OUT)
			puts("RE OUTPUT");
		if (ftoken->token  == RE_IN)
			puts("RE INPUT");
		if (ftoken->token  == HERE_DOC)
			puts("HERE_DOC");
		if (ftoken->token  == RE_OUT_A)
			puts("RE_O_APEND");
		if (ftoken->token  == ESP)
			puts("ESP");
		if (ftoken->token  == QUOTE)
			puts("QUOTE");
		if (ftoken->token  == S_QUOTE)
			puts("S_QUOTE");
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
	while (str[(*i)] && is_str(str[(*i)]))
	{
		(*i)++;
		j++;
	}
	mytoken->str = ft_substr(str, start, j);
	if (mytoken->str)
	{
		mytoken->token = WORD;
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
	}
}

void	msg_error(char *str)
{
	printf("ERR: %s\n", str);
	exit (1);
}

t_token	*get_quotes_content(char *str, int *i, char qts)
{
	int		j;
	int		start;
	t_token	*mytoken;

	(*i)++;
	j = 0;
	start = *i;
	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return (NULL);
	while (str[*i] && str[*i] != qts)
	{
		(*i)++;
		j++;
	}
	if (str[*i] == qts)
		(*i)++;
	else
		msg_error("quotes open");
	mytoken->str = ft_substr(str, start, j);
	return (mytoken);
}

void	token_quotes(t_list **mylist, char *str, int *i, char qts)
{
	t_token	*mytoken;

	mytoken = get_quotes_content(str, i, qts);
	if (mytoken->str)
	{
		mytoken->token = QUOTE;
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
	}
}

void	tokeni_mychar(t_list **mylist, int *i, int value)
{
	t_token	*mytoken;

	mytoken = malloc (sizeof (t_token));
	if (!mytoken)
		return ;
	mytoken->str = NULL;
	mytoken->token = value;
	(*i)++;
	ft_lstadd_back(mylist, ft_lstnew(mytoken));
}

void	token_spechars(t_list **mylist, char *str, int *i)
{
	if (str[*i] == '|')
		tokeni_mychar(mylist,i, PIPE);
	else if (str[*i] == ' ')
		tokeni_mychar(mylist, i, ESP);
	else if (str[*i] == '<' && str[(*i) + 1] == '<')
	{
		(*i)++;
		tokeni_mychar(mylist, i, HERE_DOC);
	}
	else if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		(*i)++;
		tokeni_mychar(mylist, i, RE_OUT_A);
	}
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
		tokeni_mychar(mylist, i, RE_IN);
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
		tokeni_mychar(mylist, i, RE_OUT);
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
		else if (str[i] == '\'')
			token_quotes(tokenizer, str, &i, '\'');
		else if (str[i] == '\"')
			token_quotes(tokenizer, str, &i, '\"');
		else if (!is_str(str[i]))
			token_spechars(tokenizer, str, &i);
	}
}

int main (int ac, char **av)
{
	t_list	*head;
	char	*str;
	char	*trimed_str;

	head = NULL;
	str = readline("minishell>> :");
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	give_tokens(&head, trimed_str);
	display_tokens(head);
	free(str);
	return (0);
}
