/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:42:54 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/31 14:57:21 by anremiki         ###   ########.fr       */
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
	if (cub->doorcheck == 1)
	{
		cub->doorcheck = 0;
		return (0);
	}
	if (!cub->doorcheck)
	{
		if (y > 0 && check_valid(map[y - 1][x], "D") && dir == 1)
			cub->doorcheck = 1;
		else if (y + 1 < cub->my && check_valid(map[y + 1][x], "D") && dir == 3)
			cub->doorcheck = 1;
		else if (x > 0 && check_valid(map[y][x - 1], "D") && dir == 2)
			cub->doorcheck = 1;
		else if (x + 1 < cub->mx && check_valid(map[y][x + 1], "D") && dir == 4)
			cub->doorcheck = 1;
	}
	return (0);
}

void	findnewlight(t_cub *cub, t_light *light, int x, int y)
{
	int	i;
	int	save;

	i = 0;
	if (cub->lights < 2)
		return ;
	while (i < cub->lights)
	{
		if ((int)light[i].x / 64 == x && (int)light[i].y / 64 == y)
		{
			save = i;
			while (i == save
				|| cub->exp[(int)light[i].y][(int)light[i].x] == '3')
				i = rand() % (cub->lights);
			Mix_PlayChannel(3, cub->teleportation, 0);
			cub->player->x = light[i].x;
			cub->player->y = light[i].y;
			cub->x = cub->player->x;
			cub->y = cub->player->y;
			cub->warp = 1;
			cub->brightness = 1;
			return ;
		}
		i++;
	}
}

int	release(int keycode, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	settings(keycode, cub);
	if (keycode == 'f')
	{
		if (cub->jump != -2)
			cub->jump = -2;
		else
			cub->jump = 0;
		raycast(cub, cub->ray);
		if (check_valid(cub->expl[(int)cub->y][(int)cub->x], LIGHTCODE))
			findnewlight(cub, cub->light, cub->x / 64, cub->y / 64);
	}
	if (check_valid(cub->expl[(int)cub->y][(int)cub->x], "K"))
		cub->exit = 1;
	if (player->released == keycode)
	{
		player->released = 0;
		player->input_fix = 0;
	}
	player->last_pressed = 0;
	return (1);
}
