/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:25:53 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/15 12:42:12 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_chunk(t_light *light, t_ray *ray)
{
	ray->rx = 0;
	ray->ry = 0;
	ray->xo = 0;
	ray->yo = 0;
	ray->ray = 0;
	ray->npx = (((int)light->x >> 6) << 6);
	ray->npy = (((int)light->y >> 6) << 6);
	ray->ra = 0.00000000000001;
	ray->r = 0;
}

void	reset_ray(t_light *light, t_ray *ray)
{
	ray->i = 0;
	ray->limit = 0;
	ray->hray = 10000000;
	ray->vray = 10000000;
	ray->hdir = 0;
	ray->vdir = 0;
	ray->hx = light->x;
	ray->hy = light->y;
	ray->vx = light->x;
	ray->vy = light->y;
	ray->contan = (-1 / tan(ray->ra));
	ray->ntan = (-tan(ray->ra));
}

void	chunk(t_cub *cub, t_light *light, t_ray *ray)
{
	init_chunk(light, ray);
	while (ray->ra <= DPI)
	{
		reset_ray(light, ray);
		lighthray(cub, light, ray, 0);
		ray->limit = 0;
		lightvray(cub, light, ray, 0);
		if (ray->hray < ray->vray)
		{
			reset_ray(light, ray);
			lighthray(cub, light, ray, 1);
		}
		else
		{
			reset_ray(light, ray);
			lightvray(cub, light, ray, 1);
		}
		ray->ra += LIGHTSTEP / 10;
	}
}
