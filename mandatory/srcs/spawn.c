/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:16:32 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:16:23 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	choose_angle(char c)
{
	if (c == 'N')
		return (deg_to_rad(0, 270));
	if (c == 'S')
		return (deg_to_rad(0, 90));
	if (c == 'E')
		return (deg_to_rad(0, 0));
	if (c == 'W')
		return (deg_to_rad(0, 180));
	return (0);
}

void	spawn_point(t_ray *ray)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (ray->map[x])
	{
		y = 0;
		while (ray->map[x][y])
		{
			if (is_charset(ray->map[x][y], "NSEW") == 0)
			{
				ray->px = y * 64 + 32;
				ray->py = x * 64 + 32;
				return ;
			}
			else
			{
				ray->px = 0;
				ray->py = 0;
			}
			y++;
		}
		x++;
	}
}

void	angle_point(t_ray *ray)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (ray->map[x])
	{
		y = 0;
		while (ray->map[x][y])
		{
			if (is_charset(ray->map[x][y], "NSEW") == 0)
			{
				ray->pa = choose_angle(ray->map[x][y]);
				ray->pdx = cos(ray->pa) * 5;
				ray->pdy = sin(ray->pa) * 5;
				return ;
			}
			y++;
		}
		x++;
	}
}

int	count_y(char **map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
			y++;
		if (y > count)
			count = y;
		x++;
	}
	return (x);
}

int	count_x(char **map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
			y++;
		if (y > count)
			count = y;
		x++;
	}
	return (count);
}
