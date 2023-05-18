# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:12:03 by mouaammo          #+#    #+#              #
#    Updated: 2023/05/18 16:45:11 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -f
CC = cc
FLAGS = -Wall -Wextra -Werror 
SRCS = $(addprefix linked_lst/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	   ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) tokenizer.c\
	   $(addprefix utils/, token_spechars.c token_word.c utils.c check_syntax.c) compiler.c parser_cmds.c

READ_LINE = $(addprefix readline/, get_next_line.c get_next_line_utils.c)

READ_LINE_OBJ = $(READ_LINE:.c=.o)
OBJS = $(SRCS:.c=.o)

HEADER1 = tokenizer.h
HEADER2 = linked_lst/linked_lst.h

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME) : $(OBJS) $(READ_LINE) $(HEADER1) $(HEADER2)
	@$(MAKE) -C libft
	@$(CC) -lreadline $(OBJS) $(READ_LINE) $(FLAGS) libft/libft.a -o $(NAME)
	@echo "====> $(NAME) is compiled"
%.o: %.c $(HEADER1) $(HEADER2)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re

