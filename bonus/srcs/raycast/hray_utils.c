/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hray_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:38:16 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/30 18:39:50 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	hdist(t_cub *cub, t_ray *ray, int flag)
{
	if (flag)
		cub->hglass = 1;
	else
		ray->htarget = cub->exp[ray->my][ray->mx];
	ray->hx = ray->rx;
	ray->hy = ray->ry;
	ray->hray = dist(cub->x, cub->y, ray->hx, ray->hy);
}

int	hdoor(t_cub *cub, t_ray *ray)
{
	ray->rx += ray->xo / 2;
	ray->ry += ray->yo / 2;
	if (((int)ray->rx % 64 - (int)cub->door) > 0 && ray->hdir == 1)
	{
		hdist(cub, ray, 1);
		return (1);
	}
	if (64 - ((int)ray->rx % 64 + (int)cub->door) > 0 && ray->hdir == 2)
	{
		hdist(cub, ray, 1);
		return (1);
	}
	ray->rx -= ray->xo / 2;
	ray->ry -= ray->yo / 2;
	return (0);
}
