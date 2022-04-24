/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:45:12 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/22 05:22:37 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//distance entre camera et ecran de projection = HALFHRES / tan(FOV)
//											   = 640 / tan(68)
//											   = 640 / 0.67450851684
//											   = 948.839019852
//
//centre ecran de projection = (HALFHRES, HALFVRES)
//							 = (640, 360)
//
//hauteur projection = (taille mur / distance mur) * distance projection
//					 = 64 / distance mur * 948.839019852
/*void	draw_sprite(t_cub *cub)
{
	float	sx = 160;
	float	sy = 192;


}*/

void	display(t_cub *cub, int draw)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->iray, 0, 0);
	//draw_sprite(cub);
	if (draw == 0 || draw == 5)
	{
		draw_posmap(cub, cub->map, ((int)cub->x >> 6), ((int)cub->y >> 6));
		draw_player(cub, ((cub->x - 3) / 64) * 16, ((cub->y - 3) / 64) * 16);
	}
}
