# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 17:38:35 by anremiki          #+#    #+#              #
#    Updated: 2022/04/17 06:53:37 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRCS =	srcs/main.c	\
		utils/parsing_utils_1.c \
		utils/parsing_utils_2.c \
		utils/utils_1.c \
		srcs/parsing_1.c \
		srcs/parsing_2.c \

#SRCS = ./expandtab.c ./crash-test/test.c

SRCS = ./srcs/parsing/check_data.c ./srcs/parsing/check_map.c \
	   ./srcs/parsing/gather_data.c ./srcs/parsing/parsing_data.c \
	   ./srcs/parsing/parsing_map.c ./srcs/parsing/parsing_utils_1.c \
	   ./srcs/parsing/init_parsing.c ./srcs/parsing/parsing_utils_2.c \
	   ./srcs/parsing/utils_1.c \
	   ./srcs/hud/draw_map.c ./srcs/hud/draw_player.c \
	   ./srcs/init/init.c ./srcs/init/textures.c \
	   ./srcs/input/key_handle.c ./srcs/input/mouse.c \
	   ./srcs/input/release.c ./srcs/input/anti_ghosting.c \
	   ./srcs/input/input.c \
	   ./srcs/utils/expandtab.c ./srcs/utils/map.c \
	   ./srcs/utils/math.c ./srcs/utils/wipe.c \
	   ./srcs/raycast/init_ray.c ./srcs/raycast/hray.c \
	   ./srcs/raycast/vray.c ./srcs/raycast/pixels.c \
	   ./srcs/raycast/floorcast.c ./srcs/raycast/skybox.c \
	   ./srcs/raycast/raycast.c ./srcs/raycast/display.c \

#SRCS = ./expandtab.c

INCLUDES = ./includes/

LIB = ./libft/libft.a ./ft_printf/libftprintf.a

OBJS = ${SRCS:.c=.o}

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCLUDES)

MLXFLAGS = ./minilibx/libmlx_Linux.a -lXext -lX11 -lXfixes -I ./minilibx/

NAME = ./exec/cub3d

PNAME = cub3d

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
		@make -C ./ft_printf
		@echo "\033[1;32mBuilding executable $(PNAME)\033[0m"
		$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIB) -o $(NAME) -lm
		@echo "#! /bin/sh" > cub3d
		@echo "xset r rate 30" >> cub3d
		@echo "xset -r 41" >> cub3d
		@echo "$(NAME) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5)" >> cub3d
		@echo "xset r rate $(DEFAULTRATE)" >> cub3d
		@echo "xset r 41" >> cub3d
		@echo
		@echo
		@echo "\033[1;41mFaut que tu lises ce qu'il y a en bas de ce msg\033[0m"
		@echo "NE SORS SURTOUT PAS DE LA MAP SINON SEGFAULT"
		@echo 
		@echo
		@echo "!!! NE QUITTE SURTOUT PAS AVEC CTRL-C !!!"
		@echo "J'ai implemente l'option pour quitter avec echap"
		@chmod +rx cub3d

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
		@echo
		@make clean -C ./ft_printf

fclean: clean
ifeq ($(NAMEEXIST), 1)
		@echo "033[1;33mClean $(PNAME)\033[0m"
else
		@echo "\033[1;31m$(PNAME) does not exist yet\033[0m"
endif
		@echo
		@echo "\033[1;33mClean mlx/.*a"
		$(RM) $(NAME) $(PNAME)
		$(RM) ./minilibx/libmlx_Linux.a
		$(RM) ./minilibx/libmlx.a
		@echo
		@make fclean -C ./libft
		@echo
		@make fclean -C ./ft_printf

re:		fclean all

.PHONY: all clean fclean re

.SILENT: all clean fclean re
