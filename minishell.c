/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:55 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/12 16:19:29 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	free_linked_list(t_list *head)
{
	t_list	*tmp;
	t_token	*mytoken;

	while (head)
	{
		mytoken = head->content;
		tmp = head->next;
		free(mytoken->str);
		free(mytoken);
		free(head);
		head = tmp;
	}
}

void	display_tokens (t_list *head)
{
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
		{
			puts("QUOTES");
			printf("[%s]\n", ftoken->str);
		}
		if (ftoken->token  == S_QUOTE)
		{
			puts("S_QUOTES");
			printf("[%s]\n", ftoken->str);
		}
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

int	myfree_func(t_list *head, char *trimed_str, char *str)
{
	free(trimed_str);
	free_linked_list(head);
	free(str);
	return (0);
}

void	*msg_error(char *str)
{
	printf("ERR: %s\n", str);
	return (0);
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
		return (free(mytoken), msg_error("quotes open"));
	mytoken->str = ft_substr(str, start, j);
	return (mytoken);
}

int	token_quotes(t_list **mylist, char *str, int *i, char qts)
{
	t_token	*mytoken;

	mytoken = get_quotes_content(str, i, qts);
	if (!mytoken)
		return (0);
	if (mytoken->str)
	{
		mytoken->token = QUOTE;
		ft_lstadd_back(mylist, ft_lstnew(mytoken));
	}
	return (1);
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
		tokeni_mychar(mylist, i, PIPE);
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

int	give_tokens(t_list **tokenizer, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_str(str[i]))
			token_word(tokenizer, str, &i);
		else if (str[i] == '\'')
		{
			if (!token_quotes(tokenizer, str, &i, '\''))
				return (0);
		}
		else if (str[i] == '\"')
		{
			if (!token_quotes(tokenizer, str, &i, '\"'))
				return (0);
		}
		else if (!is_str(str[i]))
			token_spechars(tokenizer, str, &i);
	}
	return (1);
}

void	leaks()
{
	system ("leaks minishell");
}

int	main ()
{
	t_list	*head;
	char	*str;
	char	*trimed_str;
	// atexit(leaks);
	head = NULL;
	str = readline("minishell>> :");
	if (!str)
		return (0);
	trimed_str = ft_strtrim(str, " ");
	if (!give_tokens(&head, trimed_str))
		return (myfree_func(head, trimed_str, str), 1);
	display_tokens(head);
	return (myfree_func(head, trimed_str, str));
}
