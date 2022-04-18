/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:39:55 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/18 23:14:25 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	horizon_texture(t_cub *cub, t_ray *ray, int dir)
{
	float	s;

	s = ray->shadow;
	s = 1;
	if (dir == 1)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->top, 3), s));
	if (dir == 2)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->bot, 4), s));
	if (dir == 3)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->top, 5), s));
	if (dir == 4)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->bot, 5), s));
	if (dir == 5)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->top, 8), s));
	if (dir == 6)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->bot, 8), s));
	return (shade(pxl_from_img(cub, ray->curr_px, ray->bot, 4), s));
}

void	dda_horizon(t_cub *cub, t_ray *ray)
{
	while (ray->limit < 20)
	{
		ray->mx = (int)ray->rx;
		ray->my = (int)ray->ry;
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
					ray->my > -1) && check_valid(cub->exp[ray->my][ray->mx],
						"12DPLlr"))
		{
			if (cub->exp[ray->my][ray->mx] == '2')
				ray->hdir += 2;
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->hray = dist(cub->x , cub->y, ray->hx, ray->hy);
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
