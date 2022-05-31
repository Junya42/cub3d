/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:45:12 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/31 02:02:32 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display(t_cub *cub, int draw)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->iray, 0, 0);
	if ((draw == 0 || draw == 5) && !cub->intro)
	{
		draw_posmap(cub, cub->map, ((int)cub->x >> 6), ((int)cub->y >> 6));
		draw_player(cub, ((cub->x - 3) / 64), ((cub->y - 3) / 64));
	}
}
