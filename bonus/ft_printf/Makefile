# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 03:23:44 by anremiki          #+#    #+#              #
#    Updated: 2022/04/03 16:32:46 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ./srcs/ft_printf.c ./srcs/ft_putchar.c ./srcs/ft_putnbr.c \
			  ./srcs/ft_putstr.c ./srcs/ft_putunbr.c ./srcs/ft_putx.c \
			  ./srcs/ft_putp.c

INCLUDES	= ./includes/

OBJS		= $(SRCS:.c=.o)

CC			= @gcc

RM			= @rm -rf

CFLAGS		= -Wall -Wextra -Werror -I $(INCLUDES)

NAME		= libftprintf.a

all:		$(NAME)

$(NAME):	$(OBJS)
			@echo "Building $(NAME)"
			@ar rcs $(NAME) $(OBJS)

clean:
			@echo "Cleaning $(NAME) objs"
			$(RM) $(OBJS)

fclean:		clean
			@echo "Cleaning $(NAME)"
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
