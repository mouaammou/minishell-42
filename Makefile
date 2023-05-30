# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:12:03 by mouaammo          #+#    #+#              #
#    Updated: 2023/05/30 22:54:18 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -f
CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = 	$(addprefix linked_lst/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) \
		$(addprefix new_linkedlist/, list.c) \
		$(addprefix tokenizer/, tokenizer.c) \
		$(addprefix compiler/, compiler.c) \
		$(addprefix utils/, token_spechars.c token_word.c utils.c check_syntax.c) \
		$(addprefix collecter/, collecter.c command.c expander.c heredoc.c token_db_quotes.c utils1.c utils2.c) \
		$(addprefix concate/, concatenation.c)

READ_LINE = $(addprefix readline/, get_next_line.c get_next_line_utils.c)

READ_LINE_OBJ = $(READ_LINE:.c=.o)
OBJS = $(SRCS:.c=.o)

HEADER1 = parsing.h
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

