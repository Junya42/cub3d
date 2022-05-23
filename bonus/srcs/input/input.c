/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:35:11 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/22 20:16:20 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	longitudinal(int keycode, t_player *player, char **exp, t_cub *cub)
{
	float	x;
	float	y;

	if (keycode == 'w')
	{
		foot_steps(cub, player);
		x = (player->x + (player->dx * player->ms));
		y = (player->y + (player->dy * player->ms));
		slide(cub, x, y, exp);
	}
	if (keycode == 's')
	{
		foot_steps(cub, player);
		x = (player->x - (player->dx * player->ms));
		y = (player->y - (player->dy * player->ms));
		slide(cub, x, y, exp);
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
		slide(cub, x, y, exp);
	}
	if (keycode == 'd')
	{
		foot_steps(cub, player);
		player->rstraf = secure_radians(player->angle, PI2);
		x = (player->x + cos(player->rstraf) * 5 * player->ms);
		y = (player->y + sin(player->rstraf) * 5 * player->ms);
		slide(cub, x, y, exp);
	}
}

int	save_position(t_cub *cub, t_player *player, char **exp)
{
	if (check_valid(exp[(int)player->y][(int)player->x], "12x"))
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

void	create_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 17, (1L << 17), quit, cub);
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_handle, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, release, cub);
	mlx_hook(cub->win, 6, 0x40, mouse_rotation, cub);
}
