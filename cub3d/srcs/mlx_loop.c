/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:29:03 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:15:35 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	movement(int keycode, t_ray *ray)
{
	if (keycode == UP)
	{
		ray->py += ray->pdy;
		ray->px += ray->pdx;
		ray->move = 1;
	}
	if (keycode == DOWN)
	{
		ray->py -= ray->pdy;
		ray->px -= ray->pdx;
		ray->move = 1;
	}
}

void	strafing(int keycode, t_ray *ray)
{
	if (keycode == LEFT)
	{
		ray->strafel = ray->pa - PI / 2;
		if (ray->strafel < 0)
			ray->strafel += PI * 2;
		if (ray->strafel > PI * 2)
			ray->strafel -= PI * 2;
		ray->px += cos(ray->strafel) * 5;
		ray->py += sin(ray->strafel) * 5;
		ray->move = 1;
	}
	if (keycode == RIGHT)
	{
		ray->strafer = ray->pa + PI / 2;
		if (ray->strafer < 0)
			ray->strafer += PI * 2;
		if (ray->strafer > PI * 2)
			ray->strafer -= PI * 2;
		ray->px += cos(ray->strafer) * 5;
		ray->py += sin(ray->strafer) * 5;
		ray->move = 1;
	}
}

void	move_point_of_view(int keycode, t_ray *ray)
{
	if (keycode == ARIGHT)
	{
		ray->pa += 0.1;
		if (ray->pa > 2 * PI)
			ray->pa = 0;
		ray->pdx = cos(ray->pa) * 5;
		ray->pdy = sin(ray->pa) * 5;
		ray->move = 1;
	}
	if (keycode == ALEFT)
	{
		ray->pa -= 0.1;
		if (ray->pa < 0)
			ray->pa += 2 * PI;
		ray->pdx = cos(ray->pa) * 5;
		ray->pdy = sin(ray->pa) * 5;
		ray->move = 1;
	}
}

int	key_handle(int keycode, t_ray *ray)
{
	if (keycode == ESC)
		ray->quit = 1;
	movement(keycode, ray);
	strafing(keycode, ray);
	move_point_of_view(keycode, ray);
	return (0);
}

int	rayloop(t_ray *ray)
{
	if (ray->quit == 1)
	{
		mlx_destroy_window(ray->mlx, ray->win);
		return (0);
	}
	if (ray->move == 1)
	{
		if (ray->px < 0 || ray->px > ray->width
			|| ray->py < 0 || ray->py > ray->height)
			mlx_put_image_to_window(ray->mlx, ray->win, ray->img, 0, 0);
		else
		{
			if (ray->px >= 0 && ray->px <= ray->width && ray->py >= 0
				&& ray->py <= ray->height)
				raycasting(ray);
		}
	}
	ray->move = 0;
	return (0);
}
