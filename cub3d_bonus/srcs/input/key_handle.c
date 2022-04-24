/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:45:35 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/23 07:52:21 by anremiki         ###   ########.fr       */
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
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (keycode == 65363)
	{
		player->angle = secure_radians(player->angle, 0.07);
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (keycode == 65364)
		cub->z += 15;
	if (keycode == 65362)
		cub->z -= 15;
}

void	slide(t_player *player, float x, float y, char **exp)
{
	float	ox;
	float	oy;

	ox = player->x;
	oy = player->y;
	if (!check_valid(exp[(int)player->y][(int)x], "12D"))
		player->x = x;
	if (!check_valid(exp[(int)y][(int)x], "12D"))
		player->y = y;
	if (player->x == ox && player->y == oy)
	{
		if (!check_valid(exp[(int)y][(int)ox], "12D"))
			player->y = y;
		if (!check_valid(exp[(int)y][(int)x], "12D"))
			player->x = x;
	}
}
void	longitudinal(int keycode, t_player *player, char **exp)
{
	float	x;
	float	y;

	if (keycode == 'w')
	{
		x = (player->x + (player->dx * player->ms));
		y = (player->y + (player->dy * player->ms));
		slide(player, x, y, exp);
	}
	if (keycode == 's')
	{
		x = (player->x - (player->dx * player->ms));
		y = (player->y - (player->dy * player->ms));
		slide(player, x, y, exp);
	}

}

void	lateral(int keycode, t_player *player, char **exp)
{
	float	x;
	float	y;

	if (keycode == 'a')
	{
		player->lstraf = secure_radians(player->angle, -PI2);
		x = (player->x + cos(player->lstraf) * 5 * player->ms);
		y = (player->y + sin(player->lstraf) * 5 * player->ms);
		slide(player, x, y, exp);
	}
	if (keycode == 'd')
	{
		player->rstraf = secure_radians(player->angle, PI2);
		x = (player->x + cos(player->rstraf) * 5 * player->ms);
		y = (player->y + sin(player->rstraf) * 5 * player->ms);
		slide(player, x, y, exp);
	}
}

int	save_position(t_cub *cub, t_player *player, char **exp)
{
	//t_ray *ray;

	//ray = cub->ray;
	if (check_valid(exp[(int)player->y][(int)player->x], "12D"))
	{
		player->x = player->safex;
		player->y = player->safey;
	}
	player->safex = player->x;
	player->safey = player->y;
	cub->x = player->x;
	cub->y = player->y;
	cub->a = player->angle;
	//raycast(cub, ray, 0);
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
		longitudinal(player->released, player, cub->exp);
		lateral(player->released, player, cub->exp);
	}
	rotate(keycode, cub, player);
	longitudinal(keycode, player, cub->exp);
	lateral(keycode, player, cub->exp);
	return (save_position(cub, player, cub->exp));
}
