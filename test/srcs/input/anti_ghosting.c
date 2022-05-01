/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_ghosting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:04:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/01 00:58:06 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	usleep_(long int time)
{
	while (time)
	{
		usleep(time / 10);
		time /= 10;
	}
}

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

int	anti_ghosting(t_cub *cub)
{
	t_player *player;

	player = cub->player;
	if (cub->end == 1)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		return (0);
	}
	if (!player->last_pressed && player->input_fix && player->released)
	{
		usleep_(100000);
		rotate(player->released, cub, player);
		longitudinal(player->released, player, cub->exp);
		lateral(player->released, player, cub->exp);
		save_position(cub, player, cub->exp);
	}
	(void)player;
	jump(cub);
	raycast(cub, cub->ray, 0);
	floating(cub);
	animation(cub);
	sprite_casting(cub);
	display(cub, 0);
	cub->scroll = secure_radians(cub->scroll, SKY);
	return (0);
}
