/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:24:54 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:12:09 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pxl_to_ray(t_ray *ray, float x, float y, unsigned int color)
{
	char	*tmp;
	int		size;
	int		completer;

	if (!ray->txt[0].addr)
		return ;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0 && x)
		y = 0;
	size = (int)(y * ray->txt[0].sizeline + x * (ray->txt[0].bpp / 8));
	if (size < 0 || size >= (ray->height + 32) * ray->width * 8)
		return ;
	tmp = ray->txt[0].addr + size;
	completer = 0;
	while (completer < 8)
	{
		*((unsigned int *)tmp + completer) = color;
		completer++;
	}
	(void)completer;
}

void	pxl_to_image(t_ray *ray, int a, int c, int color)
{
	char	*tmp;

	tmp = ray->addr + (c * ray->sizeline + a * (ray->bpp / 8));
	*(unsigned int *)tmp = color;
}
