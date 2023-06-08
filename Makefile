# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:12:03 by mouaammo          #+#    #+#              #
#    Updated: 2023/06/08 04:43:11 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -f
CC = cc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = 	$(addprefix Resources/linked_lst/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) \
		$(addprefix Resources/new_linkedlist/, list.c) \
		$(addprefix Resources/tokenizer/, tokenizer.c utils.c) \
		$(addprefix Resources/compiler/, compiler.c) \
		$(addprefix Resources/utils/, functions_token_1.c functions_token_2.c free_functions.c utils.c check_syntax.c) \
		$(addprefix Resources/expander/, command.c expander.c heredoc.c utils1.c utils2.c string_replace.c env.c) \
		$(addprefix Resources/readline/, get_next_line.c get_next_line_utils.c) \
		$(addprefix Resources/concate/, concate.c) \
		$(addprefix Resources/parse_list/, parse_to_double_char.c) \
		main.c

HEADERS = $(addprefix Resources/, parsing.h utils/utils.h tokenizer/tokenizer.h readline/get_next_line.h concate/concate.h\
			new_linkedlist/list.h linked_lst/linked_lst.h libft/libft.h expander/expander.h compiler/compiler.h parse_list/parser.h)
FILES = $(addprefix Resources/libft/,  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_strlen.c ft_strchr.c  ft_strncmp.c ft_strnstr.c \
		 ft_strdup.c  ft_substr.c ft_strjoin.c ft_itoa.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_strtrim.c ft_memcpy.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) $(HEADERS) $(FILES)
	@$(MAKE) -C Resources/libft
	@$(CC) -lreadline $(OBJS) $(FLAGS) Resources/libft/libft.a -o $(NAME)
	@echo "====> $(NAME) is compiled"
%.o: %.c $(HEADERS)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(MAKE) -C Resources/libft fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
