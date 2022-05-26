/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:53:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/26 17:04:30 by cmarouf          ###   ########.fr       */
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

void	compare_dist(t_cub *cub, t_ray *ray)
{
	if (ray->hray < ray->vray)
	{
		if (ray->hdir == 1)
		{
			ray->next_px = cub->top / ray->raycast;
		}
		else if (ray->hdir == 2)
		{
			ray->next_px = cub->bot / ray->raycast;
		}
		else if (ray->hdir >= 3)
		{
			ray->next_px = cub->out / ray->raycast;
			if (ray->hdir == 3)
				ray->out = (int)ray->rx % cub->out;
			else
				ray->out = cub->out - (int)ray->rx % cub->out;
		}
	}
	else
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
	else if (ray->vray < ray->hray)
	{
		ray->ray = ray->vray;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		cub->glass = cub->vglass;
	}
	ray->ray = fix_fisheye(cub->a, ray->ra, ray->ray);
	cub->zbuf[(int)ray->r] = ray->ray;
	ray->raycast = (64 * VRES / ray->ray);
	compare_dist(cub, ray);
	//ray->next_px = 64 / ray->raycast;
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
		dda_texture(cub, ray);
		float scale;
		scale = ray->shadow / ray->raycast;
		float	dim = 0;
		int		lever = 0;
		ray->end = ray->raycast + ((ray->diff - ray->raycast) / 2);
		//float	off  = ((HALFVRES - cub->z) - (ray->diff) * (0.75 - cub->h));
		/*if (cub->debug && ray->r == NRAY / 2 && ray->lag)
		{
			printf("px = %f >>> off = %f >>> offset = %f >>> lag = %d >>> z = %f\n", ray->off_px, off, ray->offset, ray->lag, cub->z);
		}*/
		//ray->end = ray->diff;
		//float	fix = 0;
		ray->i = 0;
		if (ray->lag && cub->z < 0)
			ray->i = -ray->offset * 0.33;
	//	int	fix = 0;
//		float	savepx = curr_px;
//		if (savepx > 0)
//			fix = 1;
		while (ray->i < ray->end)
		{
			if ((cub->z && ray->i >= VRES + cub->z) || (cub->z <= 0 && ray->i >= VRES))
				break ;
			ray->color = case_texture(cub, ray);
			if (flag == 0)
				ray->color = shade(ray->color, MINLIGHT);
			else
				ray->color = colorize(ray->color, ray->shadow, dim, cub->hue);
			float	ra_sky = secure_radians(ray->ra, cub->scroll) * 721;
			if (!adjacent_exp(cub, (int)ray->rx, (int)ray->ry, 32))
				if (ra_sky < cub->text[7].b && ray->i + ray->ray < cub->text[7].a)
					ray->color += shade(pxl_skybox(cub, ray->i + ray->ray, (int)ra_sky, 7), 0.05);
			//if (cub->debug && ray->r == NRAY / 2 && ray->lag)
		//		printf("i = %d\n", ray->i);
			pxl_to_ray(cub, ray->nr, (float)(int)(ray->i + ray->offset), ray->color);
			//if (fix)
		//	{
	//		}
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
