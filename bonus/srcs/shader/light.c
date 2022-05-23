/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 00:20:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/22 15:43:26 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	fix_shade(float sz, float dist, t_cub *cub, int id)
{
	float	shade;
	float	max;

	if (cub->id == id)
		cub->blocked = 1;
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
	return (count);
}

void	init_lightmath(t_cub *cub, t_ray *ray, t_lightmath *m)
{
	m->i = 0;
	ray->shadow = 0;
	m->count = 0;
	cub->hue = 0;
}

int	light(t_cub *cub, t_light *light, t_ray *ray, int ***matrix)
{
	t_lightmath	m;

	init_lightmath(cub, ray, &m);
	if (ray->rx >= 0 && ray->ry >= 0 && ray->rx < cub->ex && ray->ry < cub->ey)
	{
		while (m.i < cub->lights)
		{
			if (matrix[(int)ray->ry][(int)ray->rx][m.i] > 0)
			{
				m.dx = ray->rx - light[m.i].x;
				m.dy = ray->ry - light[m.i].y;
				m.dist = sqrt(m.dx * m.dx + m.dy * m.dy);
				m.shade = fix_shade(cub->sz, m.dist, cub, light[m.i].id);
				ray->shadow += m.shade;
				if (m.shade > 0)
				{
					m.count++;
					cub->hue += light[m.i].color;
				}
			}
			m.i++;
		}
	}
	return (add_colors(cub, ray, m.count));
}