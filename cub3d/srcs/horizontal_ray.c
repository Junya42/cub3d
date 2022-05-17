/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 01:26:19 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/17 12:20:45 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	horizontal_wall_hit(t_ray *ray)
{
	while (ray->i < 2000)
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
				ray->hx = ray->rx;
				ray->hy = ray->ry;
				ray->hray = sqrt((ray->hx - ray->px) * (ray->hx - ray->px)
						+ (ray->hy - ray->py) * (ray->hy - ray->py));
				break ;
			}
		}
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->i++;
	}
}

void	horizontal_ray(t_ray *ray)
{
	ray->i = 0;
	ray->atan = -1 / tan(ray->ra);
	if (ray->ra > PI)
	{
		ray->hdir = 1;
		ray->ry = (((int)ray->py >> 6) << 6) - 0.0001;
		ray->rx = (ray->py - ray->ry) * ray->atan + ray->px;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->atan;
	}
	if (ray->ra < PI)
	{
		ray->hdir = 2;
		ray->ry = (((int)ray->py >> 6) << 6) + 64;
		ray->rx = (ray->py - ray->ry) * ray->atan + ray->px;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->atan;
	}
	if (ray->ra == 0 || ray->ra == deg_to_rad(0, 180))
	{
		ray->rx = ray->px;
		ray->ry = ray->py;
		ray->i = ray->y;
	}
	horizontal_wall_hit(ray);
}
