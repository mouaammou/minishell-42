/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:05:15 by drtaili           #+#    #+#             */
/*   Updated: 2023/05/31 05:22:35 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =
// exist => set the value with the new one meme hta ila kant null set it with null key = "" 
// doesn't exist => add the key and set it with it's new value if the new value = NULL => key = "" 
// export : yes | env : yes

// +=
// exist => if the new value = NULL do nothing (leave the old one) else join the old value with the new one ila kant deja fiha null zid eliha new value
// doesn't exist => add the key and fill it with the new one even if the new value = NULL will be key = "" 
// export : yes | env : yes

// export key
// add key ma7dah walo => export : key
// export : yes | env : no

void	export_valid(t_list_env **env, t_list_env **export_list, char *cmd)
{
	if (check_equal_existance(cmd) && !check_plus_existance(cmd))
		export_equ_only(env, export_list, cmd);
	else if (check_equal_existance(cmd) && check_plus_existance(cmd))
		export_join(env, export_list, cmd);
	else
	{
		if (get_node_by_key(export_list, cmd) != NULL)
		{
			return ;
		}
		else
		{
			add_to_export_only(export_list, cmd);
		}
	}
}
