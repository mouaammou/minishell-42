/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/10 14:21:55 by mouaammo         ###   ########.fr       */
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
	QUOTE = 1,
	S_QUOTE = 2,
	WORD = 3,
	PIPE = 4,
	RE_OUT = 5,
	RE_IN = 6,
	RE_OUT_A = 7,
	HERE_DOC = 8,
	ESP = 9,
};

char	*join_sep(int size, char **strs, char *sep);
