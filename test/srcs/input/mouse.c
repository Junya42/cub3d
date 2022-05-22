/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:23:19 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/21 11:32:41 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_cub_angle(t_cub *cub, t_player *player)
{
	cub->a = player->angle;
	cub->cos = cos(player->angle);
	cub->sin = sin(player->angle);
}

int	mouse_rotation(int x, int y, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (x < HALFHRES - 50)
	{
		player->angle = secure_radians(player->angle, -0.013);
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (x > HALFHRES + 50)
	{
		player->angle = secure_radians(player->angle, 0.013);
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (y > HALFVRES)
		if (cub->z < 300)
			cub->z += 5;
	if (y < HALFVRES)
		if (cub->z > -300)
			cub->z -= 5;
	if (x != HALFHRES || y != HALFVRES)
		mlx_mouse_move(cub->mlx, cub->win, HALFHRES, HALFVRES);
	update_cub_angle(cub, player);
	return (0);
}
