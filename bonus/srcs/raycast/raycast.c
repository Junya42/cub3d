/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:53:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/22 13:01:17 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reset_values(t_cub *cub, t_ray *ray)
{
	ray->i = 0;
	ray->limit = 0;
	ray->hray = 1000000;
	ray->vray = 1000000;
	ray->hdir = 0;
	ray->vdir = 0;
	ray->hx = cub->x;
	ray->hy = cub->y;
	ray->vx = cub->x;
	ray->vy = cub->y;
	ray->contan = (-1 / tan(ray->ra));
	ray->ntan = (-tan(ray->ra));
}

unsigned int	case_texture(t_cub *cub, t_ray *ray)
{
	if (ray->vray < ray->hray)
	{
		if (ray->vdir % 2)
			cub->dir = 1;
		else
			cub->dir = 2;
		return (vertical_texture(cub, ray, ray->vdir));
	}
	else
	{
		if (ray->hdir % 2)
			cub->dir = 3;
		else
			cub->dir = 4;
		return (horizon_texture(cub, ray, ray->hdir));
	}
}

void	dda_texture(t_ray *ray)
{
	if (ray->shadow > 1)
		ray->shadow = 1;
	ray->curr_px = ray->next_px * ray->off_px;
	ray->top = (int)ray->rx % 64;
	ray->bot = 64 - ray->top;
	ray->right = (int)ray->ry % 64;
	ray->left = 64 - ray->right;
	ray->nr = ray->r * 4;
}

int	dda(t_cub *cub, t_ray *ray)
{
	if (ray->hray < ray->vray)
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->ray = ray->hray;
		cub->glass = cub->hglass;
	}
	if (ray->vray < ray->hray)
	{
		ray->ray = ray->vray;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		cub->glass = cub->vglass;
	}
	ray->diff = ray->ray;
	ray->ray = fix_fisheye(cub->a, ray->ra, ray->ray);
	cub->zbuf[(int)ray->r] = ray->ray;
	ray->raycast = (64 * VRES / ray->ray);
	ray->next_px = 64 / ray->raycast;
	ray->off_px = 0;
	if (ray->raycast > VRES)
	{
		ray->off_px = (ray->raycast - VRES) / 2;
		ray->raycast = VRES;
	}
	ray->offset = ((HALFVRES - cub->z) - (ray->raycast) * (0.75 - cub->h));
	return (light(cub, cub->light, ray, cub->chunk));
}

void	raycast(t_cub *cub, t_ray *ray, int draw)
{
	(void)draw;
	init_ray(cub, ray);
	int	flag = 0;
	while (ray->r < NRAY)
	{
		reset_values(cub, ray);
		hray(cub, ray);
		ray->limit = 0;
		vray(cub, ray);
		flag = dda(cub, ray);
		dda_texture(ray);
		float scale;
		scale = ray->shadow / ray->raycast;
		float	dim = 0;
		int		lever = 0;
		while (ray->i < ray->raycast)
		{
			ray->color = case_texture(cub, ray);
			if (flag == 0)
				ray->color = shade(ray->color, MINLIGHT);
			else
				ray->color = colorize(ray->color, ray->shadow, dim, cub->hue);
			float	ra_sky = secure_radians(ray->ra, cub->scroll) * 721;
			if (!adjacent_exp(cub, (int)ray->rx, (int)ray->ry, 32))
				if (ra_sky < cub->text[7].b)
					ray->color += shade(pxl_skybox(cub, ray->i + ray->ray, (int)ra_sky, 7), 0.05);
			pxl_to_ray(cub, ray->nr, (float)(int)(ray->i + ray->offset), ray->color);
			ray->curr_px += ray->next_px;
			ray->i++;
			if (dim >= ray->shadow)
				lever = 1;
			if (lever)
				dim -= scale;
			else
				dim += scale;
		}
		skybox(cub, ray);
		floorcast(cub, ray);
		ray->ra = secure_radians(ray->ra, ray->dra);
		ray->r++;
	}
}