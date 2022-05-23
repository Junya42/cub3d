# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 15:34:31 by cmarouf           #+#    #+#              #
#    Updated: 2022/05/23 18:02:53 by cmarouf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM 			= rm -f

NAME		= cub3D

NAME2 		= cubRT

all:		$(NAME)

$(NAME):
		make -C ./mandatory
clean:
			make clean -C ./mandatory
					${RM} ${NAME}
					${RM} ${NAME2}

fclean:		clean
			make fclean -C ./mandatory
			make fclean -C ./bonus

bonus:
		make -C ./bonus

re:	fclean 
	make all
					
.PHONY: all clean fclean re bonus