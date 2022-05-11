/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightvray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:14:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/11 08:52:32 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	light_vertical(t_cub *cub, t_ray *ray, t_light *light, int flag)
{
	while (ray->limit < cub->ex)
	{
		ray->mx = (int)ray->rx;
		ray->my = (int)ray->ry;
		if (ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
					ray->my > -1)
		{
			if (flag)
				cub->chunk[ray->my][ray->mx][light->id - 1] = light->id;
			if (check_valid(cub->exp[ray->my][ray->mx], "12"))
			{
				if (cub->exp[ray->my][ray->mx] == '2')
					ray->hdir += 2;
				ray->vx = ray->rx;
				ray->vy = ray->ry;
				ray->vray = dist(light->x , light->y, ray->vx, ray->vy);
				break ;
			}
		}
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->limit++;
	}
}

void	lightvray(t_cub *cub, t_light *light, t_ray *ray, int flag)
{
	if (ray->ra == NORTH || ray->ra == SOUTH)
	{
		ray->rx = light->x;
		ray->ry = light->y;
		ray->limit = cub->ex;
	}
	else if (ray->ra > PI2 && ray->ra < PI3)
	{
		ray->hdir = 1;
		ray->rx = ray->npx - 0.0001;
		ray->ry = (light->x - ray->rx) * ray->ntan + light->y;
		if (flag)
		{
			ray->ry = light->y;
			ray->rx = light->x;
		}
		//ray->ry = ray->npy - 0.0001;
		//ray->rx = (light->y - ray->ry) * ray->contan + light->x;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->ntan;
		if (flag)
		{
			ray->yo /= 64;
			ray->xo /= 64;
		}
	}
	else if (ray->ra < PI2 || ray->ra > PI3)
	{
		ray->hdir = 2;
		ray->rx = ray->npx + 64;
		ray->ry = (light->x - ray->rx) * ray->ntan + light->y;
		if (flag)
		{
			ray->ry = light->y;
			ray->rx = light->x;
		}
		//ray->ry = ray->npy + 64;
		//ray->rx = (light->y - ray->ry) * ray->contan + light->x;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->ntan;
		if (flag)
		{
			ray->yo /= 64;
			ray->xo /= 64;
		}
	}
	light_vertical(cub, ray, light, flag);
}
