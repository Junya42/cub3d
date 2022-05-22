/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:00:19 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/21 11:33:46 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	horizontal_slide(char **exp, float x, float y, t_player *player)
{
	if (!check_valid(exp[(int)player->y][(int)x], HITBOX))
		player->x = x;
	if (!check_valid(exp[(int)y][(int)x], HITBOX))
		player->y = y;
}

void	vertical_slide(char **exp, float x, float y, t_player *player)
{
	if (!check_valid(exp[(int)y][(int)player->x], HITBOX))
		player->y = y;
	if (!check_valid(exp[(int)y][(int)x], HITBOX))
		player->x = x;
}

void	update_x_y(t_player *player, float x, float y, int check)
{
	if (check)
	{
		player->x = x;
		player->y = y;
	}
}

void	cross_doors(t_cub *cub, float x, float y, t_player *player)
{
	int	check;

	check = 0;
	if (cub->degree == 1)
	{
		if (((int)y % 64) - (int)cub->door < 0)
				check = 1;
	}
	else if (cub->degree == 2)
	{
		if ((64 - (int)x % 64) - (int)cub->door < 0)
				check = 1;
	}
	else if (cub->degree == 3)
	{
		if ((64 - (int)y % 64) - (int)cub->door < 0)
				check = 1;
	}
	else if (cub->degree == 4)
	{
		if (((int)x % 64) - (int)cub->door < 0)
			check = 1;
	}
	update_x_y(player, x, y, check);
}

void	slide(t_cub *cub, float x, float y, char **exp)
{
	t_player	*player;
	float		ox;
	float		oy;

	player = cub->player;
	ox = player->x;
	oy = player->y;
	cub->degree = quadrant_direction(player->angle);
	if (exp[(int)y][(int)x] == ' ')
	{
		cross_doors(cub, x, y, player);
		return ;
	}
	horizontal_slide(exp, x, y, player);
	if (player->x == ox && player->y == oy)
		vertical_slide(exp, x, y, player);
}
