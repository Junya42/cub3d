/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 00:20:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/20 13:05:10 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	fix_shade(float sz, float dist)
{
	float shade;
	float max;
	
	shade = (1.0f / 320) * (320 - dist * sz);
	max = (1.0f / 320) * (320 - dist);
	if (shade > max)
		return (max);
	else if (shade < 0)
		return (0);
	return (shade);
}

int	fix_shadow(t_ray *ray)
{
	if (ray->shadow < MINLIGHT)
		return (0);
	else if (ray->shadow > 1)
		ray->shadow = 1;
	return (1);
}

int	add_colors(t_cub *cub, t_ray *ray, int count)
{
	if (!fix_shadow(ray))
		return (0);
	if (cub->hue == LPURPLE + LCYAN)
		cub->hue = LBLUE;
	else if (cub->hue == LPURPLE + LYELLOW)
		cub->hue = LRED;
	else if (cub->hue == LCYAN + LYELLOW)
		cub->hue = LGREEN;
	//if (count > 2)
		//cub->hue = LSHADE;
	return (count);
}

void	init_lightmath(t_cub *cub, t_ray *ray, t_lightmath *math)
{
	math->i = 0;
	ray->shadow = 0;
	math->count = 0;
	cub->hue = 0;
}

int	light(t_cub *cub, t_light *light, t_ray *ray, int ***matrix)
{
	t_lightmath	math;

	init_lightmath(cub, ray, &math);
	if (ray->rx >= 0 && ray->ry >= 0 && ray->rx < cub->ex && ray->ry < cub->ey)
	{
		while (math.i < cub->lights)
		{
			if (matrix[(int)ray->ry][(int)ray->rx][math.i] > 0)
			{
				math.dx = ray->rx - light[math.i].x;
				math.dy = ray->ry - light[math.i].y;
				math.dist = sqrt(math.dx * math.dx + math.dy * math.dy);
				math.shade = fix_shade(cub->sz, math.dist);
				ray->shadow += math.shade;
				if (math.shade > 0)
				{
					math.count++;
					cub->hue += light[math.i].color;
				}
			}
			math.i++;
		}
	}
	if (cub->debug)
	{
		if ((int)cub->x / 64 == (int)ray->rx / 64)
			if ((int)cub->y / 64 == (int)ray->ry / 64)
				printf("count = %d\n", math.count);
	}
	return (add_colors(cub, ray, math.count));
}
