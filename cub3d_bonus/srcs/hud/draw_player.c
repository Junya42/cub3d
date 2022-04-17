/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:09:46 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/11 22:10:32 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player(t_cub *cub, float x, float y)
{
	float	xmax;
	float	ymax;
	float	xsave;

	xmax = x + 7;
	ymax = y + 7;
	xsave = x;
	while (y < ymax)
	{
		x = xsave;
		while (x < xmax)
		{
			mlx_pixel_put(cub->mlx, cub->win, y, x, 0x7b00ff);
			x++;
		}
	}
}
