# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 01:16:57 by drtaili           #+#    #+#              #
#    Updated: 2023/06/11 01:42:24 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c ft_printf_utils.c ft_printf_utils2.c

OBJS = $(SRC:.c=.o)

CC = cc

RM = rm -rf

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

all: $(NAME)

%.o : %.c ft_printf.h
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY = all clean fclean re
