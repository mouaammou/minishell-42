# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 01:40:50 by mouaammo          #+#    #+#              #
#    Updated: 2023/06/10 01:48:39 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@$(MAKE) -C Resources

clean:
	rm -f main.o
	@$(MAKE) clean -C Resources
fclean: clean
	rm -f minishell
	@$(MAKE) fclean -C Resources
re:
	@$(MAKE) re -C Resources

.PHONY: all clean fclean re
