/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:39:55 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/26 21:46:16 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	horizon_door_txt(t_cub *cub, t_ray *ray, int dir)
{
	ray->top = ((int)ray->saverx - (int)cub->door) % 128;
	ray->bot = 128 - ((int)ray->saverx + (int)cub->door) % 128;
	if (dir == 1)
		return ((pxl_from_img(cub, (int)ray->curr_px % 128, ray->top, 8)));
	if (dir == 2)
		return ((pxl_from_img(cub, (int)ray->curr_px % 128, ray->bot, 8)));
	return ((pxl_from_img(cub, (int)ray->curr_px % 128, ray->bot, 8)));
}

unsigned int	horizon_texture(t_cub *cub, t_ray *ray, int dir)
{
	if (cub->glass)
		return (horizon_door_txt(cub, ray, dir));
	if (dir == 1)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->top, ray->top, 3)));
	if (dir == 2)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->bot, ray->bot, 4)));
	if (dir == 3)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->out, ray->out, 5)));
	if (dir == 4)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->out, ray->out, 5)));
	if (dir == 5)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->top, 8)));
	if (dir == 6)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->bot, 8)));
	return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->bot, 4)));
}

void	dda_horizon(t_cub *cub, t_ray *ray)
{
	cub->hglass = 0;
	while (ray->limit < cub->ey)
	{
		ray->mx = (int)ray->rx;
		ray->my = (int)ray->ry;
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1
				&& ray->my > -1) && check_valid(cub->exp[ray->my]
				[ray->mx], " "))
		{
			ray->rx += ray->xo / 2;
			ray->ry += ray->yo / 2;
			if (((int)ray->rx % 64 - (int)cub->door) > 0 && ray->hdir == 1)
			{
				cub->hglass = 1;
				ray->hx = ray->rx;
				ray->hy = ray->ry;
				ray->hray = dist(cub->x, cub->y, ray->hx, ray->hy);
				break ;
			}
			if (64 - ((int)ray->rx % 64 + (int)cub->door) > 0 && ray->hdir == 2)
			{
				cub->hglass = 1;
				ray->hx = ray->rx;
				ray->hy = ray->ry;
				ray->hray = dist(cub->x, cub->y, ray->hx, ray->hy);
				break ;
			}
			ray->rx -= ray->xo / 2;
			ray->ry -= ray->yo / 2;
		}
		if (ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1
				&& ray->my > -1 && cub->map_len[ray->my] < ray->mx)
			break ;
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1
				&& ray->my > -1) && check_valid(cub->exp[ray->my]
				[ray->mx], "12"))
		{
			if (cub->exp[ray->my][ray->mx] == '2')
				ray->hdir += 2;
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->hray = dist(cub->x, cub->y, ray->hx, ray->hy);
			break ;
		}
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->limit++;
	}
}

void	hray(t_cub *cub, t_ray *ray)
{
	if (ray->ra == PI || ray->ra == 0)
	{
		ray->hdir = 0;
		ray->rx = cub->x;
		ray->ry = cub->y;
		ray->limit = cub->ey;
	}
	else if (ray->ra > PI)
	{
		ray->hdir = 1;
		ray->ry = ray->npy - 0.0001;
		ray->rx = (cub->y - ray->ry) * ray->contan + cub->x;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->contan;
	}
	else if (ray->ra < PI)
	{
		ray->hdir = 2;
		ray->ry = ray->npy + 64;
		ray->rx = (cub->y - ray->ry) * ray->contan + cub->x;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->contan;
	}
	/*if (cub->debug && ray->r == NRAY / 2)
	{
		printf("HDIR = %d\n", ray->hdir);
		printf("hrx = %lf\n", ray->rx);
		printf("hry = %lf\n", ray->ry);
	}*/
	dda_horizon(cub, ray);
}
