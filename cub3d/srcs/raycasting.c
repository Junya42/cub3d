/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:30:05 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/17 01:27:51 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	reset_var(t_ray *ray)
{
	ray->dof = 0;
	ray->vray = 1000000;
	ray->hray = 1000000;
	ray->hx = ray->px;
	ray->hy = ray->py;
	ray->vx = ray->px;
	ray->vy = ray->py;
	ray->dby = 0;
}

void	init_var(t_ray *ray)
{
	ray->ra = ray->pa - (RAD * 60 / 2);
	if (ray->ra < 0)
		ray->ra += 2 * PI;
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
	ray->ray = 0;
}

void	next_ray(t_ray *ray)
{
	ray->ray += 1;
	ray->ra += (RAD);
	if (ray->ra < 0)
		ray->ra += 2 * PI;
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
}

void	calcul_ray_dist(t_ray *ray)
{
	ray->distt = fixfisheye(ray->pa, ray->ra, ray->distt);
	ray->wallh = 64 * ray->height / ray->distt;
	if (ray->wallh >= ray->height * 64)
		ray->wallh = ray->height * 64;
	if (ray->wallh < 0)
		ray->wallh = 0;
	ray->dy = 64.0f / ray->wallh;
	ray->offset = (ray->height / 2) - (ray->wallh / 2);
}

void	raycasting(t_ray *ray)
{
	init_var(ray);
	while (ray->ray < FOV)
	{
		reset_var(ray);
		horizontal_ray(ray);
		vertical_ray(ray);
		choose_side(ray);
		calcul_ray_dist(ray);
		texture_side(ray);
		while (ray->dof < ray->wallh)
		{
			ray->tcolor = get_txt_color(ray);
			draw_raycasting(ray, (ray->ray * 8),
				(float)(int)ray->dof + ray->offset, ray->tcolor);
			ray->dof++;
			ray->dby += ray->dy;
		}
		draw_floor(ray);
		draw_ceiling(ray);
		next_ray(ray);
	}
	mlx_put_image_to_window(ray->mlx, ray->win, ray->txt[0].img, 0, 0);
}
