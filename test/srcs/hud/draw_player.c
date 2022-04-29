/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:09:46 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/18 16:22:56 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player(t_cub *cub, float x, float y)
{
	float	xmax;
	float	ymax;
	float	ysave;

	xmax = x + 7;
	ymax = y + 7;
	ysave = y;
	while (x < xmax)
	{
		y = ysave;
		while (y < ymax)
		{
			mlx_pixel_put(cub->mlx, cub->win, x, y, 0x7b00ff);
			y++;
		}
		x++;
	}
}
