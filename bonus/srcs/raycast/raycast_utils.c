/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:12:47 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/31 02:06:37 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reset_values(t_cub *cub, t_ray *ray)
{
	ray->i = 0;
	ray->dim = 0;
	ray->lever = 0;
	ray->limit = 0;
	ray->hray = 1000000;
	ray->vray = 1000000;
	ray->hdir = 0;
	ray->vdir = 0;
	ray->hx = cub->x;
	ray->hy = cub->y;
	ray->vx = cub->x;
	ray->vy = cub->y;
	cub->vglass = 0;
	cub->hglass = 0;
	ray->htarget = 'n';
	ray->vtarget = 'n';
	ray->flag = 0;
	ray->contan = (-1 / tan(ray->ra));
	ray->ntan = (-tan(ray->ra));
}

void	compare_hdist(t_cub *cub, t_ray *ray)
{
	if (ray->hdir == 1)
		ray->next_px = cub->top / ray->raycast;
	else if (ray->hdir == 2)
		ray->next_px = cub->bot / ray->raycast;
	else if (ray->hdir >= 3)
	{
		ray->next_px = cub->out / ray->raycast;
		if (ray->hdir == 3)
			ray->out = (int)ray->rx % cub->out;
		else
			ray->out = cub->out - (int)ray->rx % cub->out;
	}
}

void	compare_vdist(t_cub *cub, t_ray *ray)
{
	if (ray->vdir == 1)
		ray->next_px = cub->right / ray->raycast;
	else if (ray->vdir == 2)
		ray->next_px = cub->left / ray->raycast;
	else if (ray->vdir >= 3)
	{
		ray->next_px = cub->out / ray->raycast;
		if (ray->vdir == 3)
			ray->out = cub->out - (int)ray->ry % cub->out;
		else
			ray->out = (int)ray->ry % cub->out;
	}
}

void	compare_dist(t_cub *cub, t_ray *ray, int flag)
{
	if (flag)
	{
		if (ray->hray < ray->vray)
			compare_hdist(cub, ray);
		else
			compare_vdist(cub, ray);
		return ;
	}
	if (ray->hray < ray->vray)
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->ray = ray->hray;
		cub->glass = cub->hglass;
		cub->target = ray->htarget;
	}
	else if (ray->vray < ray->hray)
	{
		ray->ray = ray->vray;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		cub->glass = cub->vglass;
		cub->target = ray->vtarget;
	}
}

void	get_wall_pixels(t_cub *cub, t_ray *ray)
{
	if (cub->target != '3')
		ray->color = case_texture(cub, ray);
	else
	{
		if (ray->shadow > MINLIGHT && ray->shadow < 0.6)
		{
			ray->color = cub->fcolor * ray->dim;
		}
		else if (ray->shadow > MINLIGHT)
			ray->color = cub->fcolor * 0.6;
		else
			ray->color = cub->fcolor;
	}
	if (ray->flag == 0 && !cub->intro)
		ray->color = shade(ray->color, MINLIGHT);
	else if (!cub->intro)
		ray->color = colorize(ray->color, ray->shadow, ray->dim, cub->hue);
	ray->ra_sky = secure_radians(ray->ra, cub->scroll) * 721;
	if (cub->expr[(int)ray->ry][(int)ray->rx] != '1'
		&& (cub->intro == 0 || cub->intro > 3))
		if (!adjacent_exp(cub, (int)ray->rx, (int)ray->ry, 32))
			if (ray->ra_sky < cub->text[7].b
				&& ray->i + ray->ray < cub->text[7].a)
				ray->color += shade(pxl_skybox(cub, ray->i + ray->ray,
							(int)ray->ra_sky, 7), 0.05);
}
