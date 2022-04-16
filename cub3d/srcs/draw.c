/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:28:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 01:50:29 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_raycasting(t_ray *ray, float x, float y, unsigned int color)
{
	if (x >= 0 && x <= ray->width && y >= 0 && y <= ray->height)
		pxl_to_ray(ray, x, y, color);
}

void	draw_ceiling(t_ray *ray)
{
	int	i;

	i = 0;
	if (ray->offset > ray->height)
		return ;
	while (i < ray->offset)
	{
		pxl_to_ray(ray, ray->ray * 8, i, ray->colorc);
		i++;
	}
}

void	draw_floor(t_ray *ray)
{
	int	i;

	i = ray->offset + ray->wallH;
	if (ray->offset > ray->height)
		return ;
	while (i < ray->height)
	{
		pxl_to_ray(ray, ray->ray * 8, i, ray->colorf);
		i++;
	}
}
