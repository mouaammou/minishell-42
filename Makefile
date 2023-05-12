# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:12:03 by mouaammo          #+#    #+#              #
#    Updated: 2023/05/12 17:08:14 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -f
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address
SRCS = $(addprefix linked_lst/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	   ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) minishell.c \
	   $(addprefix utils/, give_tokens.c token_spechars.c token_word.c utils.c)

OBJS = $(SRCS:.c=.o)

HEADER = minishell.h

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	@$(MAKE) -C libft
	@$(CC) -lreadline $(OBJS) $(FLAGS) libft/libft.a -o $(NAME)
	@echo "====> $(NAME) is compiled"
%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re

