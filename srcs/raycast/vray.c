/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:50:23 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/11 00:50:31 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	vertical_texture(t_cub *cub, t_ray *ray, int dir)
{
	float	s;
	float	ms;

	s = ray->shadow;
	ms = s - 0.3;
	if (ray == 1 && dir == 1)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->right, 1), s);
	if (ray == 1 && dir == 2)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->left, 2), s);
	if (ray == 1 && dir == 3)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->right, 5), ms);
	if (ray == 1 && dir == 4)
		return (shade(pxl_from_img(cub, ray->curr_px, ray->left, 5), ms);
	return (shade(pxl_from_img(cub, ray->curr_px, ray->left, 5), ms);
}

void	dda_vertical(t_cub *cub, t_ray *ray)
{
	while (ray->limit < 20)
	{
		ray->mx = (int)rx;
		ray->my = (int)ry;
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
					ray->my > -1) && check_valid(cub->exp[ray->my][ray->mx],
						"12DPLlr"))
		{
			if (cub->exp[ray->my][ray->mx] == '2')
				ray->vdir += 2;
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->vray = dist(cub->x , cub->y, ray->vx, ray->vy);
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
	}
	else if (ray->ra > PI)
	{
		ray->vdir = 1;
		ray->rx = ray->npx - 0.0001;
		ray->ry = (cub->x - ray->rx) * ray->ntan + cub->y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->ntan;
	}
	else if (ray->ra < PI)
	{
		ray->vdir = 2;
		ray->rx = ray->npx + 64;
		ray->ry = (cub->x - ray->rx) * ray->ntan + cub->y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->ntan;
	}
	dda_vertical(cub, ray);
}
