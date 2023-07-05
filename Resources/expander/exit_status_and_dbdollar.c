/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_and_dbdollar.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:21:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/04 18:13:57 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*get_string_value(char *old_str, int *index,
							char **string_key, t_list_env *myenv)
{
	char	*result_search;

	(*string_key) = NULL;
	(*string_key) = var_string(old_str, (*index), (*index));
	if (*string_key[0] == '$' && ft_strlen(*string_key) == 1)
	{
		if (old_str[*index])
			(*index)++;
		return (ft_strdup("$"));
	}
	result_search = search_for_key(*string_key + 1, myenv);
	return (result_search);
}
