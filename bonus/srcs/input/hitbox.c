/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:55:25 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/21 11:56:06 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	adjacent_exp(t_cub *cub, int x, int y, char c)
{
	char	**map;

	map = cub->exp;
	if (x < 0 || y < 0)
		return (0);
	if (y > 0 && y < cub->ey && x < cub->ex && map[y - 1][x] == c)
		return (1);
	if (y + 1 < cub->ey && x < cub->ex && map[y + 1][x] == c)
		return (1);
	if (x > 0 && x < cub->ex && y < cub->ey && map[y][x - 1] == c)
		return (1);
	if (x + 1 < cub->ex && y < cub->ey && map[y][x + 1] == c)
		return (1);
	return (0);
}

int	wall_hitbox(t_cub *cub, int x, int y, char **map)
{
	if (map[y][x] == '0' && adjacent_exp(cub, x, y, '2'))
	{
		map[y][x] = 'x';
		return (1);
	}
	else if (map[y][x] == '0' && adjacent_exp(cub, x, y, '1'))
	{
		map[y][x] = 'x';
		return (1);
	}
	return (0);
}

void	update_hitbox(t_cub *cub, int x, int y, char **map)
{
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (wall_hitbox(cub, x, y, map))
				x = 0;
			x++;
		}
		y++;
	}
}
