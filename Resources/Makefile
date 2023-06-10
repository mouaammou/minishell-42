# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:12:03 by mouaammo          #+#    #+#              #
#    Updated: 2023/06/10 01:49:19 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../minishell
RM = rm -f
CC = cc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = 	$(addprefix linked_lst/, ft_lstnew.c ft_lstadd_front.c \
					ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) \
		$(addprefix new_linkedlist/, list.c) \
		$(addprefix tokenizer/, tokenizer.c utils.c) \
		$(addprefix compiler/, compiler.c) \
		$(addprefix utils/, functions_token_1.c functions_token_2.c \
					free_functions.c utils.c check_syntax.c display.c) \
		$(addprefix expander/, exit_status_and_dbdollar.c command.c \
			expander.c heredoc.c utils1.c utils2.c string_replace.c env.c) \
		$(addprefix gnl/, get_next_line.c get_next_line_utils.c) \
		$(addprefix concate/, concate.c) \
		$(addprefix parsing/, parse_to_double_char.c parsing.c) \
		../main.c

HEADERS = $(addprefix , parsing.h utils/utils.h tokenizer/tokenizer.h \
			gnl/get_next_line.h concate/concate.h \
			new_linkedlist/list.h linked_lst/linked_lst.h libft/libft.h \
			expander/expander.h compiler/compiler.h parsing/parser.h)
FILES = $(addprefix libft/, ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c \
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
			ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_itoa.c ft_split.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_isprint.c \
			ft_putnbr_fd.c ft_strtrim.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_memcmp.c ft_memchr.c ft_bzero.c ft_calloc.c ft_striteri.c ft_strmapi.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) $(HEADERS) $(FILES)
	@$(MAKE) -C libft
	@$(CC) -lreadline $(OBJS) $(FLAGS) libft/libft.a -o $(NAME)
	@echo "====> $(NAME) is compiled"
%.o: %.c $(HEADERS)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
