/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:26:42 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/14 12:42:14 by anremiki         ###   ########.fr       */
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
	printf("doors\n");
	if (cub->doorcheck == 1)
	{
		cub->doorcheck = 0;
		return (0);
	}
	//else
	/*if (dir == 0)
		return (0);
	if (y > 0 && check_valid(map[y - 1][x], "dD") && dir == 1)
		return (swap_doors(map, x, y - 1));
	if (y + 1 < cub->my && check_valid(map[y + 1][x], "dD") && dir == 3)
		return (swap_doors(map, x, y + 1));
	if (x > 0 && check_valid(map[y][x - 1], "dD") && dir == 2)
		return (swap_doors(map, x - 1, y));
	if (x + 1 < cub->mx && check_valid(map[y][x + 1], "dD") && dir == 4)
		return (swap_doors(map, x + 1, y));*/

	if (!cub->doorcheck)
	{
		if (y > 0 && check_valid(map[y - 1][x], "dD") && dir == 1)
			cub->doorcheck = 1;
		else if (y + 1 < cub->my && check_valid(map[y + 1][x], "dD") && dir == 3)
			cub->doorcheck = 1;
		else if (x > 0 && check_valid(map[y][x - 1], "dD") && dir == 2)
			cub->doorcheck = 1;
		else if (x + 1 < cub->mx && check_valid(map[y][x + 1], "dD") && dir == 4)
			cub->doorcheck = 1;
	}
	return (0);
}

int	release(int keycode, t_cub *cub)
{
	t_player *player;

	player = cub->player;
	if (keycode == 'f')
	{
		if (cub->jump != -2)
			cub->jump = -2;
		else
			cub->jump = 0;
		/*if (doors(cub, (int)cub->x >> 6, (int)cub->y >> 6, direction(cub)))
		  {
		  free(cub->exp);
		  cub->exp = expand(cub->map, cub->mx, cub->my, 64);
		  raycast(cub, cub->ray, 0);
		  }*/
		doors(cub, (int)cub->x >> 6, (int)cub->y >> 6, direction(cub));
	}
	if (player->released == keycode)
	{
		player->released = 0;
		player->input_fix = 0;
	}
	player->last_pressed = 0;
	return (1);
}
