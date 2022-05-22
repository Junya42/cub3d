/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:22:48 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/22 19:58:08 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	jump(t_cub *cub)
{
	if (cub->jump == 1 && cub->h <= 0.50)
		cub->h += 0.01;
	if (cub->h >= 0.50)
		cub->jump = 0;
	if (cub->h > 0.25 && cub->jump == 0)
		cub->h -= 0.01;
	if (cub->h < 0.25 && cub->jump == 0)
		cub->h = 0.25;
}

void	floating(t_cub *cub)
{
	if (cub->flot == 0)
		cub->sz += 0.030;
	else if (cub->flot == 1)
		cub->sz -= 0.030;
	if (cub->sz > 7)
		cub->flot = 1;
	else if (cub->sz < 0)
		cub->flot = 0;
}

void	animation(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->nb_sprites)
	{
		if (cub->sp[i].animated == 1)
		{
			if (cub->sp[i].index >= 8)
				cub->sp[i].index = 0;
			cub->sp[i].addr = cub->sp[i].anim[(int)cub->sz].addr;
			cub->sp[i].index++;
		}
		i++;
	}
}

int	proximity(t_cub *cub, int x, int y, int dir)
{
	char	**map;

	map = cub->map;
	if (y < 0 || x < 0 || y >= cub->my || x >= cub->mx)
		return (0);
	if (y > 0 && check_valid(map[y - 1][x], "d ") && dir == 1)
		return (1);
	if (y + 1 < cub->my && check_valid(map[y + 1][x], "d ") && dir == 3)
		return (1);
	if (x > 0 && check_valid(map[y][x - 1], "d ") && dir == 2)
		return (1);
	if (x + 1 < cub->mx && check_valid(map[y][x + 1], "d ") && dir == 4)
		return (1);
	return (0);
}

void	open_door(t_cub *cub, int adj)
{
	adj = proximity(cub, (int)cub->x >> 6, (int)cub->y >> 6, direction(cub));
	if ((int)cub->y < 0 || (int)cub->x < 0 || (int)cub->y >= cub->ey || cub->x >= cub->ex)
		return ;
	if (cub->exp[(int)cub->y][(int)cub->x] != ' ')
	{
		if (adj)
		{
			if (cub->door < 60)
			{
				if (Mix_Playing(2) == 0 && cub->closed == 0)
					Mix_PlayChannel(2, cub->door_opening, 0);
				cub->door += 0.5;
				cub->closed = 1;
			}
		}
		if (!adj)
		{
			if (cub->door > 0.5)
			{
				if (Mix_Playing(2) == 0 && cub->closed == 1)
					Mix_PlayChannel(2, cub->door_opening, 0);
				cub->door -= 0.5;
				cub->closed = 0;
			}
		}
	}
}
