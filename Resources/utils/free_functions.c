/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 04:23:46 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/11 20:45:00 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_myenv(t_list_env *list)
{
	t_list_env	*tmp;
	t_env		myenv;

	while (list)
	{
		myenv = list->data;
		tmp = list->next;
		free(myenv.key);
		free(myenv.value);
		free(list);
		list = tmp;
	}
}

void	free_big_list(t_voidlst	*biglist)
{
	t_cmds		*tmp;
	t_voidlst	*cmds;
	t_voidlst	*redirs;
	t_voidlst	*temp_list;

	while (biglist)
	{
		tmp = biglist->content;
		cmds = tmp->commands;
		redirs = tmp->redirects;
		temp_list = biglist->next;
		free_voidlst(cmds);
		free_voidlst(redirs);
		free(tmp);
		free(biglist);
		biglist = temp_list;
	}
}

void	free_voidlst(t_voidlst	*list)
{
	t_voidlst	*tmp;
	t_token		*mytoken;

	while (list)
	{
		tmp = list->next;
		mytoken = list->content;
		free(mytoken->str);
		free(mytoken);
		free(list);
		list = tmp;
	}
}
