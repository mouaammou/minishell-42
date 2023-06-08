# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:12:03 by mouaammo          #+#    #+#              #
#    Updated: 2023/06/08 00:58:24 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -f
CC = cc

# FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_strlen \
# 	   ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp \
# 	   ft_strnstr ft_strlcpy ft_strlcat ft_atoi ft_strdup \
# 	   ft_substr ft_strjoin ft_itoa ft_split \
# 	   ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_isprint \
# 	   ft_putnbr_fd ft_strtrim ft_memcpy ft_memmove ft_memset \
# 	   ft_memcmp ft_memchr ft_bzero ft_calloc ft_striteri ft_strmapi
# BFILES  = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast \
# 	   ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = 	$(addprefix Resources/linked_lst/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) \
		$(addprefix Resources/new_linkedlist/, list.c) \
		$(addprefix Resources/tokenizer/, tokenizer.c utils.c) \
		$(addprefix Resources/compiler/, compiler.c) \
		$(addprefix Resources/utils/, functions_token_1.c functions_token_2.c utils.c check_syntax.c) \
		$(addprefix Resources/expander/, command.c expander.c heredoc.c utils.c string_replace.c env.c) \
		$(addprefix Resources/readline/, get_next_line.c get_next_line_utils.c) \
		main.c
		
OBJS = $(SRCS:.c=.o)

HEADER1 = Resources/parsing.h
HEADER2 = Resources/linked_lst/linked_lst.h

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME) : $(OBJS) $(HEADER1) $(HEADER2)
	@$(MAKE) -C Resources/libft
	@$(CC) -lreadline $(OBJS) $(FLAGS) Resources/libft/libft.a -o $(NAME)
	@echo "====> $(NAME) is compiled"
%.o: %.c $(HEADER1) $(HEADER2)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(MAKE) -C Resources/libft fclean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re

