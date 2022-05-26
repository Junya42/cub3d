/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:14:10 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/26 21:28:38 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_valid(char c, char *valid)
{
	int	i;

	i = 0;
	while (valid[i])
	{
		if (c == valid[i])
			return (1);
		i++;
	}
	return (0);
}

int	adjacent(t_cub *cub, int x, int y, char c)
{
	char	**map;

	map = cub->map;
	if (x < 0 || y < 0)
		return (0);
	if (y >= cub->my)
		return (0);
	if (x >= cub->width[y])
		return (0);
	if (y > 0 && x <= cub->width[y - 1] && map[y - 1][x] == c)
		return (1);
	if (y + 1 < cub->my && x <= cub->width[y + 1] && map[y + 1][x] == c)
		return (1);
	if (x > 0 && map[y][x - 1] == c)
		return (1);
	if (x + 1 < cub->mx && map[y][x + 1] == c)
		return (1);
	return (0);
}

void	revert_map(t_cub *cub, int y, int x, char **map)
{
	while (map[y])
	{
		x = ft_strlen(map[y]) - 1;
		while (map[y][x])
		{
			if (map[y][x] == '1' && adjacent(cub, x, y, '2'))
			{
				map[y][x] = '2';
				x = ft_strlen(map[y]) - 1;
			}
			x--;
			if (x < 0)
				break ;
		}
		y--;
		if (y < 0)
			break ;
	}
}
void	change_map(t_cub *cub, t_parse *parse)
{
	int		x;
	int		y;
	char	**map;

	map = cub->map;
	cub->width = parse->width;
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
	revert_map(cub, y - 1, x - 1, map);
}
