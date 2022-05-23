/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:36:33 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/23 19:25:33 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_null(t_ray *ray)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		ray->txt[i].img = NULL;
		i++;
	}
	ray->mlx = NULL;
	ray->img = NULL;
	ray->erase = NULL;
	ray->win = NULL;
}

int	get_text_addr(t_ray *ray)
{
	int	i;

	i = 1;
	ray->txt[0].img = mlx_new_image(ray->mlx, ray->width, ray->height);
	if (!ray->txt[0].img)
		return (EXIT_FAILURE);
	ray->txt[0].addr = mlx_get_data_addr(ray->txt[0].img, &ray->txt[0].bpp,
			&ray->txt[0].sizeline, &ray->txt[0].end);
	while (i < 5)
	{
		ray->txt[i].img = mlx_xpm_file_to_image
			(ray->mlx, ray->txt[i].path, &ray->txt[i].a, &ray->txt[i].b);
		if (!ray->txt[i].img)
			return (EXIT_FAILURE);
		ray->txt[i].addr = mlx_get_data_addr(ray->txt[i].img, &ray->txt[i].bpp,
				&ray->txt[i].sizeline, &ray->txt[i].end);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_mlx(t_ray *ray)
{
	init_null(ray);
	ray->mlx = mlx_init();
	if (!ray->mlx)
		return (1);
	get_text_addr(ray);
	ray->win = mlx_new_window(ray->mlx, ray->width, ray->height, "wolf3d");
	if (!ray->win)
		return (1);
	ray->erase = mlx_new_image(ray->mlx, ray->width, ray->height);
	if (!ray->erase)
		return (1);
	ray->img = mlx_new_image(ray->mlx, ray->width, ray->height);
	if (!ray->img)
		return (1);
	ray->addr = mlx_get_data_addr
		(ray->img, &ray->bpp, &ray->sizeline, &ray->end);
	mlx_put_image_to_window(ray->mlx, ray->win, ray->img, 0, 0);
	return (0);
}
