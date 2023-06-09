/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:18:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/09 17:40:15 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Resources/parsing.h"

int	main(int ac, char **av, char **env)
{
	t_list		*head;
	char		*str;
	t_voidlst	*commands;
	t_voidlst	*myenv;

	(void)ac;
	(void)av;
	myenv = take_env(env);
	while (1)
	{
		head = NULL;
		str = readline("\033[6;32mminishell>> :\033[0m");
		add_history(str);
		commands = tokenizer_and_grammar(str, head, myenv);
		if (!commands)
			continue ;
		commands = parse_to_args(commands);
		display_args(commands);
		free_and_reset(commands);
	}
	free_myenv(myenv);
	return (0);
}
