# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 15:36:33 by anremiki          #+#    #+#              #
#    Updated: 2022/03/26 17:48:46 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	./srcs/ft_isalnum.c ./srcs/ft_isprint.c ./srcs/ft_memcmp.c \
					./srcs/ft_putchar_fd.c ./srcs/ft_split.c ./srcs/ft_strlcat.c \
					./srcs/ft_strncmp.c ./srcs/ft_substr.c ./srcs/ft_atoi.c \
					./srcs/ft_isalpha.c ./srcs/ft_itoa.c ./srcs/ft_memcpy.c \
					./srcs/ft_putendl_fd.c ./srcs/ft_strchr.c  ./srcs/ft_strlcpy.c \
					./srcs/ft_strnstr.c ./srcs/ft_tolower.c ./srcs/ft_bzero.c \
					./srcs/ft_isascii.c ./srcs/ft_memmove.c \
					./srcs/ft_strdup.c  ./srcs/ft_strlen.c ./srcs/ft_putnbr_fd.c \
					./srcs/ft_strrchr.c ./srcs/ft_toupper.c ./srcs/ft_calloc.c \
					./srcs/ft_isdigit.c ./srcs/ft_memchr.c  ./srcs/ft_memset.c  \
					./srcs/ft_putstr_fd.c  ./srcs/ft_strjoin.c ./srcs/ft_strmapi.c \
					./srcs/ft_strtrim.c	./srcs/ft_arrayclear.c	./srcs/ft_isspace.c	\
					./srcs/ft_strstr.c

SRCSB			=	./srcs/ft_lstnew.c ./srcs/ft_lstadd_front.c ./srcs/ft_lstsize.c \
					./srcs/ft_lstlast.c ./srcs/ft_lstadd_back.c ./srcs/ft_lstdelone.c \
					./srcs/ft_lstclear.c ./srcs/ft_lstiter.c ./srcs/ft_lstmap.c	\
					./srcs/ft_lst_remove_if.c ./srcs/ft_lstback_new.c \
					./srcs/ft_lstdupnew.c ./srcs/ft_lstfront_new.c ./srcs/ft_lstrevsplit.c \
					./srcs/ft_lstsplit.c ./srcs/get_next_line_utils.c \
					./srcs/get_next_line.c

INCLUDES		=	./includes/

OBJS			= $(SRCS:.c=.o)

OBONUS			= $(SRCSB:.c=.o)

OBJSDIR			= objs

CC				= @gcc

RM				= rm -rf

CFLAGS			= -Wall -Wextra -Werror -I $(INCLUDES)

NAME			= libft.a

BNAME			= libft.a

PRINT			= 0

all:			$(NAME)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)
				@echo "\033[5;1;35mLibft.a : done\033[0m"

bonus:			$(NAME) $(OBONUS)
				
				@ar rcs $(NAME) $(OBONUS)
				@echo "\033[5;1;35mLibft.a bonus : done\033[0m"
clean:
				$(RM) $(OBJS) $(OBONUS)
				@echo "\033[1;33mClean libft\033[0m"

fclean:			clean
				$(RM) $(NAME)
				@echo "\033[1;33mClean libft.a\033[0m"

re:				fclean $(NAME)

.PHONY:			all clean fclean re

.SILENT:		all clean fclean re
