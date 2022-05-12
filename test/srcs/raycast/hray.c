/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:39:55 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/12 13:48:59 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	horizon_texture(t_cub *cub, t_ray *ray, int dir)
{
	float	s;

	s = ray->shadow;
	if (dir == 1)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->top, 3)));
	if (dir == 2)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->bot, 4)));
	if (dir == 3)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->top, 5)));
	if (dir == 4)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->bot, 5)));
	if (dir == 5)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->top, 8)));
	if (dir == 6)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->bot, 8)));
	(void)s;
	return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->bot, 4)));
}

void	dda_horizon(t_cub *cub, t_ray *ray)
{
	//ray->rx = cub->x;
	//ray->ry = cub->y;
	while (ray->limit < cub->ey)
	{
		ray->mx = (int)ray->rx;
		ray->my = (int)ray->ry;
		//if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
		//			ray->my > -1))
	//	{
//			if (cub->exp[ray->my][ray->mx] != '1')
//				if (cub->exp[ray->my][ray->mx] != '2')
//					cub->exp[ray->my][ray->mx] = '*';
//		}
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
					ray->my > -1) && check_valid(cub->exp[ray->my][ray->mx],
						"12"))
		{
			if (cub->exp[ray->my][ray->mx] == '2')
				ray->hdir += 2;
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->hray = dist(cub->x , cub->y, ray->hx, ray->hy);
		//	cub->exp[ray->my][ray->mx] = '*';
			break ;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->limit++;
		}
	}
}

void	hray(t_cub *cub, t_ray *ray)
{
	if (ray->ra == PI || ray->ra == 0)
	{
		ray->rx = cub->x;
		ray->ry = cub->y;
		ray->limit = 20;
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
	dda_horizon(cub, ray);
}
