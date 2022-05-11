/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:45:35 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/11 08:01:47 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate(int keycode, t_cub *cub, t_player *player)
{
	if (keycode == 'c')
	{
		if (cub->jump == 0)
		{
			cub->jump = -1;
			if (cub->h == 0.25)
				cub->h = 0.12;
		}
	}
	if (keycode == 32)
	{
		if (cub->h == 0.25)
		{
			cub->jump = 1;
		}
		else if (cub->h < 0.25 && cub->jump == -1)
			cub->jump = 0;
	}
	if (keycode == 65361)
	{
		player->angle = secure_radians(player->angle, -0.07);
		cub->cos = cos(player->angle);
		cub->sin = sin(player->angle);
		player->dx = cub->cos * 5;
		player->dy = cub->sin * 5;
	}
	if (keycode == 65363)
	{
		player->angle = secure_radians(player->angle, 0.07);
		cub->cos = cos(player->angle);
		cub->sin = sin(player->angle);
		player->dx = cub->cos * 5;
		player->dy = cub->sin * 5;
	}
	if (keycode == 65364)
		if (cub->z < 300)
			cub->z += 15;
	if (keycode == 65362)
		if (cub->z > -300)
			cub->z -= 15;
}

void	slide(t_player *player, float x, float y, char **exp)
{
	float	ox;
	float	oy;

	ox = player->x;
	oy = player->y;
	if (!check_valid(exp[(int)player->y][(int)x], "12Dx"))
		player->x = x;
	if (!check_valid(exp[(int)y][(int)x], "12Dx"))
		player->y = y;
	if (player->x == ox && player->y == oy)
	{
		if (!check_valid(exp[(int)y][(int)ox], "12Dx"))
			player->y = y;
		if (!check_valid(exp[(int)y][(int)x], "12Dx"))
			player->x = x;
	}
}

void	foot_steps(t_cub *cub, t_player *player)
{
	Mix_Volume(0, 32);
	cub->mixing++;
	cub->foot = 0;
	cub->time_move = timestamp();
	cub->lastx = player->x;
	cub->lasty = player->y;
}

void	longitudinal(int keycode, t_player *player, char **exp, t_cub *cub)
{
	float	x;
	float	y;

	if (keycode == 'w')
	{
		foot_steps(cub, player);
		x = (player->x + (player->dx * player->ms));
		y = (player->y + (player->dy * player->ms));
		slide(player, x, y, exp);
	}
	if (keycode == 's')
	{
		foot_steps(cub, player);
		x = (player->x - (player->dx * player->ms));
		y = (player->y - (player->dy * player->ms));
		slide(player, x, y, exp);
	}

}

void	lateral(int keycode, t_player *player, char **exp, t_cub *cub)
{
	float	x;
	float	y;

	if (keycode == 'a')
	{
		foot_steps(cub, player);
		player->lstraf = secure_radians(player->angle, -PI2);
		x = (player->x + cos(player->lstraf) * 5 * player->ms);
		y = (player->y + sin(player->lstraf) * 5 * player->ms);
		slide(player, x, y, exp);
	}
	if (keycode == 'd')
	{
		foot_steps(cub, player);
		player->rstraf = secure_radians(player->angle, PI2);
		x = (player->x + cos(player->rstraf) * 5 * player->ms);
		y = (player->y + sin(player->rstraf) * 5 * player->ms);
		slide(player, x, y, exp);
	}
}

int	save_position(t_cub *cub, t_player *player, char **exp)
{
	if (check_valid(exp[(int)player->y][(int)player->x], "12Dx"))
	{
		player->x = player->safex;
		player->y = player->safey;
	}
	player->safex = player->x;
	player->safey = player->y;
	cub->x = player->x;
	cub->y = player->y;
	cub->a = player->angle;
	return (0);
}

int key_handle(int keycode, t_cub *cub)
{
	t_player *player;

	player = cub->player;
	if (keycode == 'r')
		cub->z = 0;
	if (keycode == 65307)
		cub->end = 1;
	if (player->released && player->released != keycode)
	{
		player->last_pressed = keycode;
		player->input_fix = 1;
	}
	if (!player->released)
		player->released = keycode;
	if (player->released != keycode)
	{
		rotate(player->released, cub, player);
		longitudinal(player->released, player, cub->exp, cub);
		lateral(player->released, player, cub->exp, cub);
	}
	rotate(keycode, cub, player);
	longitudinal(keycode, player, cub->exp, cub);
	lateral(keycode, player, cub->exp, cub);
	return (save_position(cub, player, cub->exp));
}
