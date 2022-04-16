/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:23:19 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/16 18:34:54 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_rotation(int x, int y, t_cub *cub, t_player *player)
{
	if (x < HALFHRES)
	{
		player->angle = secure_radians(player->angle, -0.002);
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (x > HALFHRES)
	{
		player->angle = secure_radians(player->angle, 0.002);
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (x < (HALFHRES - THIRDH) || x > (HALFHRES + THIRDH))
		mlx_mouse_move(cub->mlx, cub->win, HALFHRES, HALFVRES);
	else if (y < (HALFVRES - THIRDV) || y > (HALFVRES + THIRDV))
		mlx_mouse_move(cub->mlx, cub->win, HALFHRES, HALFVRES);
	cub->a = player->angle;
	return (0);
}
