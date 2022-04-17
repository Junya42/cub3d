/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 01:26:06 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/17 01:21:37 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	choose_side(t_ray *ray)
{
	if (ray->hray < ray->vray)
	{
		ray->wallc = shade(0x8c03fc, 0.7);
		ray->distt = ray->hray;
		ray->rx = ray->hx;
		ray->ry = ray->hy;
	}
	if (ray->vray < ray->hray)
	{
		ray->wallc = 0x8c03fc;
		ray->distt = ray->vray;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
	}
}

void	texture_side(t_ray *ray)
{
	ray->north = (int)ray->rx % 64;
	ray->south = 64 - ray->north;
	ray->east = (int)ray->ry % 64;
	ray->west = 64 - ray->east;
}
