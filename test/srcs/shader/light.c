/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 00:20:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/11 10:57:22 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	light(t_cub *cub, t_light *light, t_ray *ray, int ***matrix)
{
	float	dist;
	float	dx;
	float	dy;
	float	shade;
	float	max;
	int		i;
	int		count;

	i = 0;
	int	bonus = 0;
	ray->shadow = 0;
	count = 0;
	if (ray->rx >= 0 && ray->ry >= 0 && ray->rx < cub->ex && ray->ry < cub->ey)
	{
		while (i < cub->lights)
		{
			if (matrix[(int)ray->ry][(int)ray->rx][i] > 0)
			{
				dx = ray->rx - light[i].x;
				dy = ray->ry - light[i].y;
				dist = sqrt(dx * dx + dy * dy);
				shade = (1.0f / 320) * (320 - dist * cub->sz);
				max = (1.0f / 320) * (320 - dist);
				if (i == 1 && ray->r == NRAY / 2)
				{
					if (ray->rx < light[i].x && ray->ry < light[i].y)
						bonus = 180;
					else if (ray->rx < light[i].x && ray->ry > light[i].y)
						bonus = 180;
					else if (ray->rx > light[i].x && ray->ry < light[i].y)
						bonus = 360;
					else
						bonus = 0;
					(void)bonus;
					//printf("angle of light to wall = %f\n", atan(dy/dx) * 180 / PI + bonus);
					
				}
				if (shade > max)
					shade = max;
				if (shade < 0)
					shade = 0;
				if (i == 0)
					ray->l1 = shade;
				if (i > 0)
					ray->l2 = shade;
				ray->shadow += shade;
				count += light[i].id;
				//printf("shade = %f\n", shade);
			}
			i++;
		}
	}
	//exit (0);
	if (ray->shadow > 1)
		ray->shadow = 1;
	if (ray->shadow < MINLIGHT)
	{
		ray->shadow = MINLIGHT;
		return (0);
	}
	(void)matrix;
	return (count);
}
