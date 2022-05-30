/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighthray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:45:02 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/27 14:02:25 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	end_lhray(t_cub *cub, t_ray *ray, t_light *light)
{
	if (cub->exp[ray->my][ray->mx] == '2')
		ray->hdir += 2;
	ray->hx = ray->rx;
	ray->hy = ray->ry;
	ray->hray = dist(light->x, light->y, ray->hx, ray->hy);
}

void	light_horizon(t_cub *cub, t_ray *ray, t_light *light, int flag)
{
	while (ray->limit < cub->ey)
	{
		ray->mx = (int)ray->rx;
		ray->my = (int)ray->ry;
		if (ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1
			&& ray->my > -1)
		{
			if (flag)
			{
				ray->hray = dist(light->x, light->y, ray->rx, ray->ry);
				if (ray->hray <= 320)
					cub->chunk[ray->my][ray->mx][light->id - 1] = light->id;
			}
			if (cub->map_len[ray->my] < ray->mx)
				break ;
			if (check_valid(cub->exp[ray->my][ray->mx], "12"))
			{
				end_lhray(cub, ray, light);
				break ;
			}
		}
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->limit++;
	}
}

void	topray(t_ray *ray, t_light *light, int flag)
{
	ray->hdir = 1;
	ray->ry = ray->npy - 0.0001;
	ray->rx = (light->y - ray->ry) * ray->contan + light->x;
	if (flag)
	{
		ray->ry = light->y;
		ray->rx = light->x;
	}
	ray->yo = -64;
	ray->xo = -ray->yo * ray->contan;
	if (flag)
	{
		ray->yo /= 64;
		ray->xo /= 64;
	}
}

void	botray(t_ray *ray, t_light *light, int flag)
{
	ray->hdir = 2;
	ray->ry = ray->npy + 64;
	ray->rx = (light->y - ray->ry) * ray->contan + light->x;
	if (flag)
	{
		ray->ry = light->y;
		ray->rx = light->x;
	}
	ray->yo = 64;
	ray->xo = -ray->yo * ray->contan;
	if (flag)
	{
		ray->yo /= 64;
		ray->xo /= 64;
	}
}

void	lighthray(t_cub *cub, t_light *light, t_ray *ray, int flag)
{
	if (ray->ra == PI || ray->ra == 0)
	{
		ray->rx = light->x;
		ray->ry = light->y;
		ray->limit = cub->ey;
	}
	else if (ray->ra > PI)
		topray(ray, light, flag);
	else if (ray->ra < PI)
		botray(ray, light, flag);
	light_horizon(cub, ray, light, flag);
}
