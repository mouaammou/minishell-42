/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/08 20:10:18 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "linked_lst/linked_lst.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct token
{
	char	*str;
	int		token;
}t_token;

enum	tokens
{
	t_quotes = 1,
	t_single_quotes = 2,
	t_word = 3,
	t_pipe = 4
};

char	*join_sep(int size, char **strs, char *sep);
