/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:14:10 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/16 18:20:30 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	adjacent(t_cub *cub, int x, int y, char c)
{
	char **map;

	map = cub->map;
	if (y > 0 && map[y - 1][x] == c)
		return (1);
	if (y + 1 < cub->my && map[y + 1][x] == c)
		return (1);
	if (x > 0 && map[y][x - 1] == c)
		return (1);
	if (x + 1 < cub->mx && cub[y][x + 1] == c)
		return (1);
	return (0);
}

void	change_map(t_cub *cub)
{
	int		x;
	int		y;
	char	**map;

	map = cub->map;
	x = 0;
	y = 0;
	while (map[y][x] && map[y][x] == 32)
		x++;
	map[y][x] = '2';
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1' && adjacent(cub, x, y, '2'))
			{
				map[y][x] = '2';
				x = 0;
			}
			x++;
		}
		y++;
	}
}
