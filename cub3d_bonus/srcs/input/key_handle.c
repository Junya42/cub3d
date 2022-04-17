/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:45:35 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 06:24:17 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate(int keycode, t_player *player)
{
	if (keycode == 'q')
	{
		player->angle = secure_radians(player->angle, -0.07);
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (keycode == 'e')
	{
		player->angle = secure_radians(player->angle, 0.07);
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
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
		if (!check_valid(exp[(int)player->y][(int)x], "12D"))
			player->x = x;
		if (!check_valid(exp[(int)y][(int)x], "12D"))
			player->y = y;
	}
	if (keycode == 's')
	{
		x = (player->x - (player->dx * player->ms));
		y = (player->y - (player->dy * player->ms));
		if (!check_valid(exp[(int)player->y][(int)x], "12D"))
			player->x = x;
		if (!check_valid(exp[(int)y][(int)x], "12D"))
			player->y = y;
	}

}

void	lateral(int keycode, t_player *player, char **exp)
{
	float	x;
	float	y;

	if (keycode == 'a')
	{
		player->lstraf = secure_radians(player->angle, -PI2);
		x = (player->x + sin(player->lstraf) * 5 * player->ms);
		y = (player->y + cos(player->lstraf) * 5 * player->ms);
		if (!check_valid(exp[(int)player->y][(int)x], "12D"))
			player->x = x;
		if (!check_valid(exp[(int)y][(int)x], "12D"))
			player->y = y;
	}
	if (keycode == 'd')
	{
		player->rstraf = secure_radians(player->angle, PI2);
		x = (player->x + sin(player->rstraf) * 5 * player->ms);
		y = (player->y + cos(player->rstraf) * 5 * player->ms);
		if (!check_valid(exp[(int)player->y][(int)x], "12D"))
			player->x = x;
		if (!check_valid(exp[(int)y][(int)x], "12D"))
			player->y = y;
	}
}

int	save_position(t_cub *cub, t_player *player, char **exp)
{
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
	raycast(cub, cub->ray);
	return (0);
}

int key_handle(int keycode, t_cub *cub, t_player *player)
{
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
		rotate(player->released, player);
		longitudinal(player->released, player, cub->exp);
		lateral(player->released, player, cub->exp);
	}
	rotate(keycode, player);
	longitudinal(keycode, player, cub->exp);
	lateral(keycode, player, cub->exp);
	return (save_position(cub, player, cub->exp));
}
