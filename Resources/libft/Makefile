CC = cc
RM = rm -f
AR = ar -crs
FLAGS = -Wall -Werror -Wextra
NAME = libft.a
#########################
#### mandatory part

FILES = ft_isalpha ft_isdigit ft_isalnum ft_strlen ft_strchr  ft_strncmp \
		ft_strnstr ft_strdup  ft_substr ft_strjoin ft_itoa ft_split \
		ft_putchar_fd ft_putstr_fd ft_strtrim ft_memcpy
	        
## Object files
OBJ=$(FILES:=.o)
#########################
### my targests
all: $(NAME)
	@echo "----- Mandatory Part Compiled."

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(NAME) is created"

%.o: %.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(BOBJ)
	@echo "--- Object files are Cleand."

fclean: clean
	@$(RM) $(NAME)
	@echo "--- ALL Cleand."

re: fclean all
.PHONY: all fclean clean re
