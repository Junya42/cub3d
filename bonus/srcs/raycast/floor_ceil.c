/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:53:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/30 17:57:17 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ceiling(t_cub *cub, t_ray *ray)
{
	float			fix;
	unsigned int	color;
	int				end;

	ray->j = ray->offset + ray->raycast;
	end = ray->offset;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	while (end >= 0)
	{
		ray->offj = ray->j - (HALFVRES - cub->z);
		ray->floor_x = cub->x / 2 + cos(ray->ra) * 200 * 64 / ray->offj / fix;
		ray->floor_y = cub->y / 2 + sin(ray->ra) * 200 * 64 / ray->offj / fix;
		color = pxl_from_img(cub, (int)ray->floor_y % 64,
				(int)ray->floor_x % 64, 6);
		pxl_to_ray(cub, ray->nr, end, color);
		end--;
		ray->j++;
	}
}

void	glass(t_cub *cub, float x, float y, float lvl)
{
	unsigned int	color;

	color = pxl_from_img(cub, x, y, -1);
	color = colorize(color, 0.55, 0.55, SHADE);
	pxl_to_ray(cub, (int)x, (int)y, color);
	(void)lvl;
}

void	init_floorcast(t_cub *cub, t_ray *ray, t_cast *c)
{
	ray->raycast = ray->end;
	ray->j = ray->offset + ray->raycast;
	c->fix = fix_fisheye(cub->a, ray->ra, 1);
	c->distx = cos(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	c->disty = sin(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	c->dceilx = cos(ray->ra) * 360 * 32 * (0.75 + cub->h);
	c->dceily = sin(ray->ra) * 360 * 32 * (0.75 + cub->h);
	ray->offj = ray->j - (HALFVRES - cub->z);
	c->heightfix = VRES;
	if (cub->z < 0)
		c->heightfix -= cub->z * 2;
	c->i = -1;
	c->limiter = 0;
}
