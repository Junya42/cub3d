/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:50:23 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/31 15:29:33 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	vert_door_txt(t_cub *cub, t_ray *ray, int dir)
{
	ray->right = ((int)ray->savery - (int)cub->door) % 128;
	ray->left = 128 - ((int)ray->savery + (int)cub->door) % 128;
	if (dir == 1)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->right, 8)));
	if (dir == 2)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 8)));
	if (dir == 3)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->right, 8)));
	if (dir == 4)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 8)));
	return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 8)));
}

unsigned int	vertical_texture(t_cub *cub, t_ray *ray, int dir)
{
	if (cub->glass)
		return (vert_door_txt(cub, ray, dir));
	if (dir == 1)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->right
					, ray->right, 1)));
	if (dir == 2)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->left
					, ray->left, 2)));
	if (dir == 3)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->out, ray->out, 5)));
	if (dir == 4)
		return ((pxl_from_img(cub, (int)ray->curr_px % cub->out, ray->out, 5)));
	return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 5)));
}

void	dda_vertical(t_cub *cub, t_ray *ray)
{
	while (ray->limit < cub->ex)
	{
		ray->mx = (int)ray->rx;
		ray->my = (int)ray->ry;
		if (ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1
			&& ray->my > -1 && cub->map_len[ray->my] < ray->mx)
			break ;
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1
				&& ray->my > -1) && check_valid(cub->exp[ray->my]
				[ray->mx], " d"))
			if (vdoor(cub, ray))
				break ;
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1
				&& ray->my > -1) && check_valid(cub->exp[ray->my]
				[ray->mx], "123"))
		{
			if (cub->exp[ray->my][ray->mx] == '2')
				ray->vdir += 2;
			vdist(cub, ray, 0);
			break ;
		}
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->limit++;
	}
}

void	vray(t_cub *cub, t_ray *ray)
{
	if (ray->ra == PI || ray->ra == 0)
	{
		ray->vdir = 0;
		ray->rx = cub->x;
		ray->ry = cub->y;
		ray->limit = 20;
	}
	else if (ray->ra > PI2 && ray->ra < PI3)
	{
		ray->vdir = 1;
		ray->rx = ray->npx - 0.0001;
		ray->ry = (cub->x - ray->rx) * ray->ntan + cub->y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->ntan;
	}
	else if (ray->ra < PI2 || ray->ra > PI3)
	{
		ray->vdir = 2;
		ray->rx = ray->npx + 64;
		ray->ry = (cub->x - ray->rx) * ray->ntan + cub->y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->ntan;
	}
	dda_vertical(cub, ray);
}
