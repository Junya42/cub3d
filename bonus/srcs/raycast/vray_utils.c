/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vray_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:40:08 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/30 18:40:24 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	vdist(t_cub *cub, t_ray *ray, int flag)
{
	if (flag)
		cub->vglass = 1;
	else
		ray->vtarget = cub->exp[ray->my][ray->mx];
	ray->vx = ray->rx;
	ray->vy = ray->ry;
	ray->vray = dist(cub->x, cub->y, ray->vx, ray->vy);
}

int	vdoor(t_cub *cub, t_ray *ray)
{
	ray->rx += ray->xo / 2;
	ray->ry += ray->yo / 2;
	if (((int)ray->ry % 64 - (int)cub->door) > 0 && ray->vdir == 1)
	{
		vdist(cub, ray, 1);
		return (1);
	}
	if (64 - ((int)ray->ry % 64 + (int)cub->door) > 0 && ray->vdir == 2)
	{
		vdist(cub, ray, 1);
		return (1);
	}
	ray->rx += ray->xo / 2;
	ray->ry += ray->yo / 2;
	return (0);
}
