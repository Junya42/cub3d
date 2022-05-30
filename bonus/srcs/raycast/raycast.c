/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:53:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/30 20:24:54 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	dda_texture(t_cub *cub, t_ray *ray)
{
	if (ray->shadow > 1)
		ray->shadow = 1;
	ray->curr_px = ray->next_px * ray->off_px;
	ray->bigpx = ray->bignpx * ray->off_px;
	ray->saverx = (int)ray->rx;
	ray->savery = (int)ray->ry;
	ray->bot = (int)ray->rx % cub->top;
	ray->top = cub->bot - ((int)ray->rx % cub->bot);
	ray->right = (int)ray->ry % cub->right;
	ray->left = cub->left - ((int)ray->ry % cub->left);
	ray->nr = ray->r * 4;
}

int	dda(t_cub *cub, t_ray *ray)
{
	compare_dist(cub, ray, 0);
	ray->ray = fix_fisheye(cub->a, ray->ra, ray->ray);
	cub->zbuf[(int)ray->r] = ray->ray;
	ray->raycast = (64 * VRES / ray->ray);
	compare_dist(cub, ray, 1);
	ray->bignpx = 128 / ray->raycast;
	ray->off_px = 0;
	ray->diff = ray->raycast;
	ray->lag = 0;
	if (ray->raycast > VRES)
	{
		ray->lag = 1;
		ray->off_px = (ray->raycast - VRES) / 2;
		ray->raycast = VRES;
	}
	ray->lx = ray->rx;
	ray->ly = ray->ry;
	ray->end = ray->raycast + ((ray->diff - ray->raycast) / 2);
	ray->offset = ((HALFVRES - cub->z) - (ray->raycast) * (0.75 - cub->h));
	return (light(cub, cub->light, ray, cub->chunk));
}

void	init_shade(t_cub *cub, t_ray *ray, int flag)
{
	if (flag)
	{
		ray->flag = dda(cub, ray);
		dda_texture(cub, ray);
		ray->scale = ray->shadow / ray->raycast;
		ray->end = ray->raycast + ((ray->diff - ray->raycast) / 2);
		if (ray->lag && cub->z < 0)
			ray->i = -ray->offset * 0.33;
	}
	else
	{
		ray->curr_px += ray->next_px;
		ray->i++;
		if (ray->dim >= ray->shadow)
			ray->lever = 1;
		if (ray->lever)
			ray->dim -= ray->scale;
		else
			ray->dim += ray->scale;
	}
}

void	raycast(t_cub *cub, t_ray *ray)
{
	init_ray(cub, ray);
	while (ray->r < NRAY)
	{
		reset_values(cub, ray);
		hray(cub, ray);
		ray->limit = 0;
		vray(cub, ray);
		init_shade(cub, ray, 1);
		while (ray->i < ray->end)
		{
			if ((cub->z && ray->i >= VRES + cub->z)
				|| (cub->z <= 0 && ray->i >= VRES))
				break ;
			get_wall_pixels(cub, ray);
			pxl_to_ray(cub, ray->nr,
				(float)(int)(ray->i + ray->offset), ray->color);
			init_shade(cub, ray, 0);
		}
		skybox(cub, ray);
		floorcast(cub, ray);
		ray->ra = secure_radians(ray->ra, ray->dra);
		ray->r++;
	}
}
