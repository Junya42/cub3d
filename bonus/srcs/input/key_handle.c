/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:45:35 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/31 13:47:45 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotation(int keycode, t_player *player, t_cub *cub)
{
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
}

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
	rotation(keycode, player, cub);
	if (keycode == 65364)
		if (cub->z < 300)
			cub->z += 15;
	if (keycode == 65362)
		if (cub->z > -300)
			cub->z -= 15;
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

void	options(int keycode, t_cub *cub)
{
	if (keycode == 'r')
		cub->z = 0;
	if (keycode == 'p')
		cub->pause = 0;
	if (keycode == 'o')
		cub->pause = 1;
	if (keycode == 65307)
		cub->end = 1;
}

int	key_handle(int keycode, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	options(keycode, cub);
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
		save_position(cub, player, cub->exp);
	}
	rotate(keycode, cub, player);
	longitudinal(keycode, player, cub->exp, cub);
	lateral(keycode, player, cub->exp, cub);
	return (save_position(cub, player, cub->exp));
}
