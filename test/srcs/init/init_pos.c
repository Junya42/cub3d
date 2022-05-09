/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:05:01 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/09 12:05:40 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_angle(t_cub *cub, char dir)
{
	if (dir == 'N')
		cub->a = 4.71238;
	else if (dir == 'E')
		cub->a = 0;
	else if (dir == 'S')
		cub->a = PI / 2;
	else if (dir == 'W')
		cub->a = PI;
	else
		cub->a = 4.71238;
}

void    get_map_xy(char **map, t_cub *cub)
{
	int     y;
	int     x;
	int     max;

	y = 0;
	x = 0;
	max = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (check_valid(map[y][x], "NSEW"))
			{
				cub->x = x * 64 + 32;
				cub->y = y * 64 + 32;
				get_angle(cub, map[y][x]);
			}
			x++;
		}
		if (x > max)
			max = x;
		y++;
	}
	cub->mx = max;
	cub->my = y;
}