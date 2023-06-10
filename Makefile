# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 01:40:50 by mouaammo          #+#    #+#              #
#    Updated: 2023/06/10 01:43:00 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@$(MAKE) -C Resources

clean:
	@$(MAKE) clean -C Resources
fclean: clean
	@$(MAKE) fclean -C Resources

re:
	@$(MAKE) re -C Resources

.PHONY: all clean fclean re
