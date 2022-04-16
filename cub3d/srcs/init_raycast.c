/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:26:45 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:04:36 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_texture_rgb(t_ray *ray, t_parse *parse)
{
	ray->txt[0].path = NULL;
	ray->txt[1].path = parse->npath;
	ray->txt[2].path = parse->spath;
	ray->txt[3].path = parse->epath;
	ray->txt[4].path = parse->wpath;
	ray->colorc = parse->colorc;
	ray->colorf = parse->colorf;
}

void	get_text_addr(t_ray *ray)
{
	int	i;

	i = 1;
	ray->txt[0].img = mlx_new_image(ray->mlx, ray->width, ray->height);
	ray->txt[0].addr = mlx_get_data_addr(ray->txt[0].img, &ray->txt[0].bpp,
			&ray->txt[0].sizeline, &ray->txt[0].end);
	while (i < 5)
	{
		ray->txt[i].img = mlx_xpm_file_to_image
			(ray->mlx, ray->txt[i].path, &ray->txt[i].a, &ray->txt[i].b);
		ray->txt[i].addr = mlx_get_data_addr(ray->txt[i].img, &ray->txt[i].bpp,
				&ray->txt[i].sizeline, &ray->txt[i].end);
		i++;
	}
}

void	init_mlx_var(t_ray *ray, t_parse *parse)
{
	ray->quit = 0;
	ray->move = 0;
	ray->firsta = 1;
	ray->map = parse->map + 6;
}

void	init_position_var(t_ray *ray)
{
	ray->pdx = cos(ray->pa) * 5;
	ray->pdy = sin(ray->pa) * 5;
	ray->mlx = mlx_init();
	ray->width = count_x(ray->map) * blocSize;
	ray->height = count_y(ray->map) * blocSize;
	ray->x = count_x(ray->map);
	ray->y = count_y(ray->map);
}

void	init_raycasting(t_parse *parse)
{
	t_ray	ray;

	init_mlx_var(&ray, parse);
	get_texture_rgb(&ray, parse);
	spawn_point(&ray);
	angle_point(&ray);
	init_position_var(&ray);
	get_text_addr(&ray);
	ray.win = mlx_new_window(ray.mlx, 480, ray.height, "wolf3d");
	ray.erase = mlx_new_image(ray.mlx, ray.width, ray.height);
	ray.img = mlx_new_image(ray.mlx, ray.width, ray.height);
	ray.addr = mlx_get_data_addr(ray.img, &ray.bpp, &ray.sizeline, &ray.end);
	mlx_put_image_to_window(ray.mlx, ray.win, ray.img, 0, 0);
	raycasting(&ray);
	mlx_loop_hook(ray.mlx, &rayloop, &ray);
	mlx_hook(ray.win, 17, (1L << 17), &quit, &ray);
	mlx_hook(ray.win, KeyPress, KeyRelease, &key_handle, &ray);
	mlx_loop(ray.mlx);
	free_data(parse);
	free_mlx(&ray);
}
