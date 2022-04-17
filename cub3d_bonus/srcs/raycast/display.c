/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:45:12 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 06:51:05 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->iray, 0, 0);
	draw_posmap(cub, cub->map, ((int)cub->x >> 6), ((int)cub->y >> 6));
	draw_player(cub, ((int)(cub->x - 3) >> 6) * 16, ((int)(cub->y - 3) >> 6) * 16);
}
