/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/13 22:00:13 by anremiki         ###   ########.fr       */
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
		color = pxl_from_img(cub, (int)ray->floor_y % 64, (int)ray->floor_x % 64, 6);
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

void	floorcast(t_cub *cub, t_ray *ray)
{
	float			fix;
	unsigned int	color;
	float			distx;
	float			disty;
	int				jumpfix;

	ray->j = ray->offset + ray->raycast;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	distx = cos(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	disty = sin(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	ray->offj = ray->j - (HALFVRES - cub->z);
	jumpfix = 0;
	if (cub->h < 0.25)
		jumpfix = 49;
	float heightfix = VRES;
	if (cub->z < 0)
		heightfix -= cub->z * 2;
	int	i = -1;
	int		limiter = 0;
	while (ray->j < heightfix)
	{
		ray->offj = ray->j - (HALFVRES - cub->z);
		ray->floor_x = cub->x / 2 + distx / ray->offj / fix;
		ray->floor_y = cub->y / 2 + disty / ray->offj / fix;
		float	ra_sky = secure_radians(ray->ra, cub->scroll) * 721;
		int	ceilcheck = 0;
		if (((int)(ray->floor_y) >> 5) > -1 && ((int)(ray->floor_x) >> 5) > -1)
			if (cub->map[((int)(ray->floor_y) >> 5)][((int)(ray->floor_x) >> 5)] == 32)
				ceilcheck = 1;
		if (!ceilcheck)
		{
			if (ra_sky < cub->text[7].b)
				cub->scolor = pxl_skybox(cub, ray->j - (ray->offset + ray->raycast) + HALFVRES, (int)ra_sky, 7);
			color = cub->scolor;
		}
		else
			color = 0;
		if (limiter < ray->raycast)
			color += shade(case_texture(cub, ray), MINLIGHT);
		color += pxl_from_img(cub, (int)ray->floor_y % 64, (int)ray->floor_x % 64, 6);
		//if (limiter < ray->raycast)
		//	color += case_texture(cub, ray);
		ray->rx = (int)ray->floor_x * 2;
		ray->ry = (int)ray->floor_y * 2;
		int flag = light(cub, cub->light, ray, cub->chunk);
		if (flag == 0)
		{
				color = shade(color, MINLIGHT);
		}
		else if (flag == 1)
			color = colorize(color, ray->shadow, ray->shadow, PURPLE);
		else if (flag == 2)
			color = colorize(color, ray->shadow, ray->shadow, CYAN);
		else if (flag == 3)
			color = colorize(color, ray->shadow, ray->shadow, YELLOW);
		pxl_to_ray(cub, ray->nr, ray->j, color);
		if (ceilcheck)
		{
			color = pxl_from_img(cub, (int)ray->floor_y % 64, (int)ray->floor_x % 64, 5);
			if (flag == 0)
				color = shade(color, 0.05);
			else if (flag == 1)
				color = colorize(color, ray->shadow, ray->shadow - cub->sz / 5, PURPLE);
			else if (flag == 2)
				color = colorize(color, ray->shadow, ray->shadow - cub->sz / 5, CYAN);
			else if (flag == 3)
				color = colorize(color, ray->shadow, ray->shadow - cub->sz / 5, YELLOW);
			//color = colorize(color, ray->shadow, ray->shadow - cub->sz / 5, PURPLE);
			pxl_to_ray(cub, ray->nr, (int)((ray->offset - i * (1.25 - cub->h))), color);
		}
		//if (ceilcheck)
		//	glass(cub, ray->nr, (int)(ray->offset - i), MINLIGHT);
		/*if (cub->map[((int)(ray->floor_y) >> 5)][((int)(ray->floor_x) >> 5)] == 32)
		  if ((VRES - cub->z - (ray->j + cub->z) > 0))
		  glass(cub, ray->nr, (VRES - cub->z - (ray->j + cub->z)), lvl);*/
		//glass(cub, ray->nr, (int)(ray->offset - i), lvl);
		ray->j++;
		i++;
		limiter++;
		ray->curr_px -= ray->next_px;
	}
	(void)jumpfix;
}
