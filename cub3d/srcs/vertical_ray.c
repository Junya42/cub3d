/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 01:26:30 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:16:46 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	vertical_wall_hit(t_ray *ray)
{
	while (ray->i < ray->x && ray->rx < ray->width && ray->ry < ray->height)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * ray->width + ray->mx;
		if ((ray->mx > -1) && (ray->my > -1) && (ray->mx < ray->width)
			&& (ray->my < ray->height))
		{
			if (out_of_bound(ray->map, ray->my, ray->mx))
				break ;
			if (ray->map[ray->my][ray->mx] == '1')
			{
				ray->vx = ray->rx;
				ray->vy = ray->ry;
				ray->vray = sqrt((ray->vx - ray->px) * (ray->vx - ray->px)
						+ (ray->vy - ray->py) * (ray->vy - ray->py));
				break ;
			}
		}
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->i++;
	}
}

void	vertical_ray(t_ray *ray)
{
	ray->i = 0;
	ray->ntan = -tan(ray->ra);
	if (ray->ra > (PI / 2) && ray->ra < (3 * (PI / 2)))
	{
		ray->vdir = 1;
		ray->rx = (((int)ray->px >> 6) << 6) - 0.0001;
		ray->ry = (ray->px - ray->rx) * ray->ntan + ray->py;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->ntan;
	}
	if (ray->ra < (PI / 2) || ray->ra > (3 * (PI / 2)))
	{
		ray->vdir = 2;
		ray->rx = (((int)ray->px >> 6) << 6) + 64;
		ray->ry = (ray->px - ray->rx) * ray->ntan + ray->py;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->ntan;
	}
	if (ray->ra == 0 || ray->ra == deg_to_rad(0, 180))
	{
		ray->rx = ray->px;
		ray->ry = ray->py;
		ray->i = ray->x;
	}
	vertical_wall_hit(ray);
}
