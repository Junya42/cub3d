/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_ghosting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:04:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/18 14:51:11 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	jump(t_cub *cub)
{
	if (cub->jump == 1 && cub->h <= 0.50)
		cub->h += 0.01;
	if (cub->h >= 0.50)
		cub->jump = 0;
	if (cub->h > 0.25 && cub->jump == 0)
		cub->h -= 0.01;
	if (cub->h < 0.25 && cub->jump == 0)
		cub->h = 0.25;
}

void	floating(t_cub *cub)
{
	if (cub->flot == 0)
		cub->sz += 0.030;
	else if (cub->flot == 1)
		cub->sz -= 0.030;
	if (cub->sz > 7)
		cub->flot = 1;
	else if (cub->sz < 0)
		cub->flot = 0;
}

void	animation(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->nb_sprites)
	{
		if (cub->sp[i].animated == 1)
		{
			if (cub->sp[i].index >= 8)
				cub->sp[i].index = 0;
			cub->sp[i].addr = cub->sp[i].anim[(int)cub->sz].addr; 
			cub->sp[i].index++;
		}
		i++;
	}
}
int	proximity(t_cub *cub, int x, int y, int dir)
{
	char **map;

	map = cub->map;
	if (y > 0 && check_valid(map[y - 1][x], "d ") && dir == 1)
		return (1);
	if (y  + 1 < cub->my && check_valid(map[y + 1][x], "d ") && dir == 3)
		return (1);
	if (x > 0 && check_valid(map[y][x - 1], "d ") && dir == 2)
		return (1);
	if (x  + 1 < cub->mx && check_valid(map[y][x + 1], "d ") && dir == 4)
		return (1);
	return (0);
}

void	open_door(t_cub *cub)
{
	int	adj;

	adj = proximity(cub, (int)cub->x >> 6, (int)cub->y >> 6, direction(cub));
	if (cub->exp[(int)cub->y][(int)cub->x] != ' ')
	{
		if (adj)
		{
			if (cub->door < 60)
			{
				if (Mix_Playing(2) == 0 && cub->closed == 0)
					Mix_PlayChannel(2, cub->door_opening, 0);
				cub->door += 0.5;
				cub->closed = 1;
			}
		}
		if (!adj)
		{
			if (cub->door > 0.5)
			{
				cub->door -= 0.5;
				cub->closed = 0;
			}
		}
	}
}

void	update_3d_sound(t_cub *cub, t_player *player)
{
	if (cub->mixing >= 4)
		cub->mixing = 0;
	cub->curr_time = timestamp();
	if (cub->sp_dist > 250)
		cub->sp_dist = 250;
	Mix_SetPosition(1, (int)cub->sp_angle, cub->sp_dist);
	if (cub->curr_time - cub->time_move >= 300)
	{
		if (player->x == cub->lastx && player->y == cub->lasty)
		{
			Mix_FadeOutChannel(0, 200);
			cub->foot = 1;
		}
		else
		{
			cub->lastx = player->x;
			cub->lasty = player->y;
		}
	}
	if (Mix_Playing(0) == 0 && cub->foot != 1)
		Mix_PlayChannel(0, cub->foot_steps[cub->mixing], -1);
}

int	anti_ghosting(t_cub *cub)
{
	t_player *player;

	player = cub->player;
	/*if (cub->map[(int)cub->y / 64][(int)cub->x / 64] == '3')
	{
		player->x = 4 * 64 + 32;
		player->y = 7 * 64 + 32;
		cub->x = player->x;
		cub->y = player->y;
	}*/
	if (cub->end == 1)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		return (0);
	}
	if (!player->last_pressed && player->input_fix && player->released)
	{
		usleep_(100000);
		rotate(player->released, cub, player);
		longitudinal(player->released, player, cub->exp, cub);
		lateral(player->released, player, cub->exp, cub);
		save_position(cub, player, cub->exp);
	}
	update_3d_sound(cub, player);
	jump(cub);
	open_door(cub);
	raycast(cub, cub->ray, 0);
	if (cub->pause == 1)
		floating(cub);
	animation(cub);
	sprite_casting(cub);
	display(cub, 0);
	cub->scroll = secure_radians(cub->scroll, SKY);
	return (0);
}
