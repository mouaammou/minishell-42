# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 00:14:07 by mouaammo          #+#    #+#              #
#    Updated: 2023/07/05 14:08:55 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC =	main.c main_tools.c free_tools.c \
		$(addprefix execution/,cd.c tools.c cd_tools.c execute.c env_functions.c exit_status.c env_functions_tools.c pwd.c exit.c \
		echo.c env.c unset.c is_builtin.c export.c execute_tools.c pipe_cases.c \
		tools_env.c tools_env_.c check_arg_export.c export_tools.c valid_args_export.c \
		export_all_cases.c pipe.c redirections.c) \
		$(addprefix Resources/linked_lst/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) \
		$(addprefix Resources/new_linkedlist/, list.c) \
		$(addprefix Resources/tokenizer/, tokenizer.c utils.c) \
		$(addprefix Resources/compiler/, compiler.c) \
		$(addprefix Resources/utils/, display.c free_functions.c functions_token_1.c functions_token_2.c utils.c check_syntax.c) \
		$(addprefix Resources/expander/, command.c expander.c heredoc.c utils1.c string_replace.c utils2.c exit_status_and_dbdollar.c env.c ) \
		$(addprefix Resources/concate/, concate.c ) \
		$(addprefix Resources/parsing/, parse_to_double_char.c parsing.c )

HEADERS = $(addprefix Resources/, parsing.h utils/utils.h tokenizer/tokenizer.h \
			concate/concate.h \
			new_linkedlist/list.h linked_lst/linked_lst.h libft/libft.h \
			expander/expander.h compiler/compiler.h parsing/parser.h) \
			ft_printf/ft_printf.h minishell.h
FILES = $(addprefix Resources/libft/, ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c \
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
			ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_itoa.c ft_split.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_isprint.c \
			ft_putnbr_fd.c ft_strtrim.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_memcmp.c ft_memchr.c ft_bzero.c ft_calloc.c ft_striteri.c ft_strmapi.c) \
		$(addprefix ft_printf/, ft_printf.c ft_printf_utils.c ft_printf_utils2.c)

# Object files
OBJS = $(SRC:.c=.o)

# Compiler
CC = cc -fsanitize=address -g

# Compiler flags
# FLAGS := -Wall -Wextra -Werror

BOLDGREEN=\033[1m\033[32m
RESET = \033[0m


# Readline flags
RLFLAGS := -lreadline
# LFLAGSS := -L /Users/${USER}/goinfre/.brew/opt/readline/lib
# IFLAGS := -I /Users/${USER}/goinfre/.brew/opt/readline/include

LFLAGSS="-L/Users/mouaammo/.brew/opt/readline/lib"
IFLAGS="-I/Users/mouaammo/.brew/opt/readline/include"

# Command-line utilities
RM := rm -rf

# Target executable
NAME := minishell

# Library dependencies
LIBFT := ./Resources/libft/libft.a 
PRINTF := ./ft_printf/libftprintf.a 
PATH_LIBFT := ./Resources/libft
PATH_PRINTF := ./ft_printf

# The default target
all: $(NAME)                                                                                     
# Build the dependencies
$(LIBFT):
	@make -C $(PATH_LIBFT)
	@make -C $(PATH_PRINTF)
	@echo "\033[1m\033[32m LIBFT COMPILED \033[0m"
	@echo "\033[1m\033[32m FT_PRINTF COMPILED \033[0m"

# Build the target executable
$(NAME): $(LIBFT) $(OBJS) $(HEADERS) $(FILES) $(PRINTF)
	@$(CC) $(FLAGS) $(RLFLAGS) $(LFLAGSS) $(OBJS) -o $(NAME) $(LIBFT) $(PRINTF)
	@echo "\033[1m\033[32m MINISHELL CREATED \033[0m"
# Build object files
%.o: %.c  $(HEADERS) $(FILES)
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@
	@echo $<
# Clean the object files and dependencies
clean:
	@$(RM) $(OBJS)
	@make clean -C $(PATH_LIBFT)
	@make clean -C $(PATH_PRINTF)

# Remove all generated files
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(PATH_LIBFT)
	@make fclean -C $(PATH_PRINTF)

# Clean and rebuild the target executable
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re bonus
