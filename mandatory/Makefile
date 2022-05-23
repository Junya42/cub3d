# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 17:38:35 by anremiki          #+#    #+#              #
#    Updated: 2022/05/23 16:14:25 by cmarouf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/main.c	\
		utils/parsing_utils_1.c \
		utils/parsing_utils_2.c \
		utils/utils_1.c \
		srcs/parsing_data.c \
		srcs/parsing_map.c \
		srcs/init_parsing.c \
		srcs/check_data.c \
		srcs/check_map.c \
		srcs/gather_data.c \
		srcs/spawn.c \
		srcs/spawn_bis.c \
		srcs/init_raycast.c \
		srcs/raycasting.c \
		srcs/quit.c \
		srcs/mlx_loop.c \
		srcs/draw.c \
		srcs/math.c \
		srcs/pixel.c \
		srcs/texture.c \
		srcs/texture_position.c \
		srcs/horizontal_ray.c \
		srcs/vertical_ray.c \
		srcs/create_mlx.c \


INCLUDES = ./includes/

LIB = ./libft/libft.a 

OBJS = ${SRCS:.c=.o}

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCLUDES)

MLXFLAGS = ./minilibx/libmlx_Linux.a -lXext -lX11 -I ./minilibx/

NAME = ./exec/cub3D

NAME2 = ./mandatory/exec/cub3D

NAME3 = ../cub3D

PNAME = cub3D

CC = @gcc

ARG1 = "$$"1

ARG2 = "$$"2

ARG3 = "$$"3

ARG4 = "$$"4

ARG5 = "$$"5

NAMEEXIST = $(shell ls ./exec/ | grep -F $(PNAME) | wc -l)

TOTAL = $(shell ls ./srcs/ | grep -F .c | wc -l)

CURRENT = $(shell ls ./srcs/ | grep -F .o | wc -l | xargs expr 1 +)

COMPARE = $(shell expr $(TOTAL) + 1)

DEFAULTRATE = $(shell xset -q | grep delay | awk '{printf"%d", $$4}')

.c.o:
		@echo "Building $< $(CURRENT)/$(TOTAL)"
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -lm

all:	$(NAME)

$(NAME): $(OBJS)
		@echo
		@echo "\033[1;32mBuilding minilibx\033[0m"
		@echo
		@make -C ./minilibx
		@echo "\033[1;32mBuilding libft\033[0m"
		@make bonus -C ./libft
		@echo "\033[1;32mBuilding executable $(PNAME)\033[0m"
		$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIB) -o $(NAME) -lm
		@echo "#! /bin/sh" > ../cub3D
		@echo "xset r rate 30" >> ../cub3D
		@echo "$(NAME2) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5)" >> ../cub3D
		@echo "xset r rate $(DEFAULTRATE)" >> ../cub3D
		@echo
		@echo
		@echo "\033[1;41mFaut que tu lises ce qu'il y a en bas de ce msg\033[0m"
		@echo "NE SORS SURTOUT PAS DE LA MAP SINON SEGFAULT"
		@echo 
		@echo
		@echo "!!! NE QUITTE SURTOUT PAS AVEC CTRL-C !!!"
		@echo "J'ai implemente l'option pour quitter avec echap"
		@chmod +rx ../cub3D

clean:
ifeq ($(CURRENT), $(COMPARE))
		@echo "\033[1;33mClean $(PNAME) objs\033[0m"
else
		@echo "\033[1;31m$(PNAME) has no objs\033[0m"
endif
		$(RM) $(OBJS)
		@echo
		@echo "\033[1;33mClean minilibx\033[0m"
		@make clean -C ./minilibx
		@echo
		@make clean -C ./libft

fclean: clean
ifeq ($(NAMEEXIST), 1)
		@echo "033[1;33mClean $(PNAME)\033[0m"
else
		@echo "\033[1;31m$(PNAME) does not exist yet\033[0m"
endif
		@echo
		@echo "\033[1;33mClean mlx/.*a"
		$(RM) $(NAME) $(PNAME) $(NAME3)
		$(RM) ./minilibx/libmlx_Linux.a
		$(RM) ./minilibx/libmlx.a
		@echo
		@make fclean -C ./libft

re:		fclean 
		make all

.PHONY: all clean fclean re

.SILENT: all clean fclean re
