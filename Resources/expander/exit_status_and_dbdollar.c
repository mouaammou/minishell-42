/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_and_dbdollar.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:21:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/15 20:57:01 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*exit_status_value(char **string_key, int *index)
{
	char	*string_value;

	string_value = NULL;
	string_value = ft_itoa(g_global_exit.exit_status);
	free(*string_key);
	*string_key = ft_strdup("$?");
	(*index)++;
	return (string_value);
}

char	*get_string_value(char *old_str, int *index,
							char **string_key, t_list_env *myenv)
{
	(*string_key) = NULL;
	(*string_key) = var_string(old_str, (*index), (*index));
	if (*string_key[0] == '$' && ft_strlen(*string_key) == 1)
	{
		if (old_str[*index])
			(*index)++;
		return (ft_strdup("$"));
	}
	return (search_for_key(*string_key + 1, myenv));
}
