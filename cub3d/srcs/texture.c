/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:24:32 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:18:20 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	shade(int color, float shader)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) * shader;
	g = ((color >> 8) & 0x00ff) * shader;
	b = (color & 0x0000ff) * shader;
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

unsigned int	get_texture_color(t_ray *ray, int y, int x, int i)
{
	char	*tmp;
	int		size;

	if (y == 0 && x < 0)
		x = 0;
	if (y < 0 && x)
		y = 0;
	size = (int)(y * ray->txt[i].sizeline + x * (ray->txt[i].bpp / 8));
	if (size < 0 || size >= (ray->height + 32) * ray->width * 4)
		return (0x000000);
	tmp = ray->txt[i].addr + size;
	return (*(unsigned int *)tmp);
}

unsigned int	hcolor(t_ray *ray)
{
	if (ray->hdir == 1)
		return (shade(get_texture_color(ray, ray->dby, ray->north, 3), 0.8));
	if (ray->hdir == 2)
		return (get_texture_color(ray, ray->dby, ray->south, 4));
	return (get_texture_color(ray, ray->dby, ray->south, 1));
}

unsigned int	vcolor(t_ray *ray)
{
	if (ray->vdir == 1)
		return (get_texture_color(ray, ray->dby, ray->west, 1));
	if (ray->vdir == 2)
		return (get_texture_color(ray, ray->dby, ray->east, 2));
	return (get_texture_color(ray, ray->dby, ray->west, 1));
}

unsigned int	get_txt_color(t_ray *ray)
{
	if (ray->hray < ray->vray)
		return (hcolor(ray));
	else
		return (vcolor(ray));
}
