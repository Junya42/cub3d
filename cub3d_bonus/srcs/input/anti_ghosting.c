/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_ghosting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:04:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/25 01:51:25 by anremiki         ###   ########.fr       */
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
		cub->h -= 0.02;
	if (cub->h < 0.25 && cub->jump == 0)
		cub->h = 0.25;
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
	//sprite_casting(cub);
	display(cub, 0);
	/*if (cub->scroll > 0)
	  cub->scroll = -VRES;
	  cub->scroll += 0.2;*/
	return (0);
}
