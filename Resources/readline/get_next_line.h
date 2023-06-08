/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:59:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/18 16:06:33 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<unistd.h>
# include<stdlib.h>
# include "../libft/libft.h"

char	*get_next_line(int fd);
int		check_new_line(char *str);
char	*str_join(char *s1, char *s2);
char	*get_reminder(char **str, int len);
char	*get_my_line(char **temp, char *line, int ln);

#endif
