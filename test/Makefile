# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 19:16:48 by anremiki          #+#    #+#              #
#    Updated: 2022/05/21 13:00:57 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./srcs/parsing/check_data.c ./srcs/parsing/check_map.c \
	   ./srcs/parsing/gather_data.c ./srcs/parsing/parsing_data.c \
	   ./srcs/parsing/parsing_map.c ./srcs/parsing/parsing_utils_1.c \
	   ./srcs/parsing/init_parsing.c ./srcs/parsing/parsing_utils_2.c \
	   ./srcs/utils/utils_1.c ./srcs/parsing/utils_1.c \
	   ./srcs/shader/chunks.c \
	   ./srcs/shader/matrix_utils.c ./srcs/shader/matrix.c \
	   ./srcs/shader/lighthray.c ./srcs/shader/lightvray.c \
	   ./srcs/shader/chunkcasting.c ./srcs/shader/light.c \
	   ./srcs/init/init_cub.c ./srcs/animation/animate.c \
	   ./srcs/hud/draw_map.c ./srcs/hud/draw_player.c \
	   ./srcs/init/init.c ./srcs/init/textures.c \
	   ./srcs/input/collision.c ./srcs/input/hitbox.c \
	   ./srcs/input/key_handle.c ./srcs/input/mouse.c \
	   ./srcs/input/release.c ./srcs/input/anti_ghosting.c \
	   ./srcs/input/input.c \
	   ./srcs/utils/expandtab.c ./srcs/utils/map.c \
	   ./srcs/utils/math.c ./srcs/utils/wipe.c \
	   ./srcs/utils/degree.c \
	   ./srcs/shader/colors.c ./srcs/shader/shade.c \
	   ./srcs/raycast/init_ray.c ./srcs/raycast/hray.c \
	   ./srcs/raycast/vray.c ./srcs/raycast/pixels.c \
	   ./srcs/raycast/floor_ceil.c \
	   ./srcs/raycast/floorcast.c ./srcs/raycast/skybox.c \
	   ./srcs/raycast/raycast.c ./srcs/raycast/display.c \
	   ./srcs/sprites/init_sprites.c ./srcs/sprites/sprites_casting.c \
	   ./srcs/sprites/sprites_parsing.c ./srcs/sprites/s_light_blue.c \
	   ./srcs/sprites/s_light_cyan.c ./srcs/sprites/s_light_green.c \
	   ./srcs/sprites/s_light_purple.c ./srcs/sprites/s_light_red.c \
	   ./srcs/sprites/s_light_yellow.c ./srcs/sprites/s_light.c \
	   ./srcs/utils/time.c ./srcs/sound/init_audio.c \
	   ./srcs/init/init_pos.c ./srcs/sprites/start_sprites.c \
	   ./srcs/init/quit.c ./srcs/init/create_window.c \
	   ./srcs/parsing/get_map_len.c ./srcs/sprites/choose_sprite_texture.c \

INCLUDES = ./includes/

LIB = ./libft/libft.a ./SDL_MIXER/lib/libSDL2_mixer.a

OBJS = ${SRCS:.c=.o}

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCLUDES) -O0

MLXFLAGS = ./minilibx/libmlx_Linux.a -lXext -lX11 -I ./minilibx/ -I ./SDL_MIXER/include/SDL2

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
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -lm -I ./SDL_MIXER/include/SDL2

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
		$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIB) -o $(NAME) -lm -lSDL2
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

re:		fclean 
		make all

.PHONY: all clean fclean re

.SILENT: all clean fclean re
