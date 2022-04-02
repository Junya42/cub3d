# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 15:36:33 by anremiki          #+#    #+#              #
#    Updated: 2022/04/02 18:04:01 by anremiki         ###   ########.fr        #
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
					./srcs/ft_strtrim.c

SRCSB			=	./srcs/ft_lstnew.c ./srcs/ft_lstadd_front.c ./srcs/ft_lstsize.c \
					./srcs/ft_lstlast.c ./srcs/ft_lstadd_back.c ./srcs/ft_lstdelone.c \
					./srcs/ft_lstclear.c ./srcs/ft_lstiter.c ./srcs/ft_lstmap.c

INCLUDES		=	./includes/

OBJS			= $(SRCS:.c=.o)

OBONUS			= $(SRCSB:.c=.o)
CC				= @gcc

RM				= @rm -f

CFLAGS			= -Wall -Wextra -Werror -I $(INCLUDES)

NAME			= libft.a

BNAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)

bonus:			$(OBONUS)
				@ar rcs $(NAME) $(OBONUS)
clean:
				$(RM) $(OBJS) $(OBONUS)

fclean:			clean
				$(RM) $(NAME) $(OBONUS)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
