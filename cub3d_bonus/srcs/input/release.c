/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:26:42 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 06:24:48 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	swap_doors(char **map, int x, int y)
{
	if (map[y][x] == 'd')
		map[y][x] = 'D';
	else if (map[y][x] == 'D')
		map[y][x] = 'd';
	return (1);
}

int	direction(t_cub *cub)
{
	if (cub->a >= PI3 - PIOFF && cub->a <= PI3 + PIOFF)
		return (1);
	else if (cub->a >= PI - PIOFF && cub->a <= PI + PIOFF)
		return (2);
	else if (cub->a >= PI2 - PIOFF && cub->a <= PI2 + PIOFF)
		return (3);
	else if (cub->a >= DPI - PIOFF || cub->a <= 0 + PIOFF)
		return (4);
	return (0);
}

int	doors(t_cub *cub, int x, int y, int dir)
{
	char	**map;

	map = cub->map;
	if (dir == 0)
		return (0);
	if (y > 0 && check_valid(map[y - 1][x], "dD") && dir == 1)
		return (swap_doors(map, x, y - 1));
	if (y + 1 < cub->my && check_valid(map[y + 1][x], "dD") && dir == 3)
		return (swap_doors(map, x, y + 1));
	if (x > 0 && check_valid(map[y][x - 1], "dD") && dir == 2)
		return (swap_doors(map, x - 1, y));
	if (x + 1 < cub->mx && check_valid(map[y][x + 1], "dD") && dir == 4)
		return (swap_doors(map, x + 1, y));
	return (0);
}

int	release(int keycode, t_cub *cub, t_player *player)
{
	if (keycode == 'f')
	{
		if (doors(cub, (int)cub->x >> 6, (int)cub->y >> 6, direction(cub)))
		{
			free(cub->exp);
			cub->exp = expand(cub->map, cub->mx, cub->my, 64);
			raycast(cub, cub->ray);
		}
	}
	if (player->released == keycode)
	{
		player->released = 0;
		player->input_fix = 0;
	}
	player->last_pressed = 0;
	return (1);
}
