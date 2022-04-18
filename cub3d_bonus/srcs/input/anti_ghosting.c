/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_ghosting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:04:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/18 03:08:24 by anremiki         ###   ########.fr       */
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

int	anti_ghosting(t_cub *cub)
{
	t_player *player;

	player = cub->player;
	if (cub->end == 1)
		mlx_destroy_window(cub->mlx, cub->win);
	if (!player->last_pressed && player->input_fix && player->released)
	{
		printf("ANTIGHOSTING\n");
		printf("before anti px = %f >>> py = %f\n", player->x, player->y);
		usleep_(30*10000);
		rotate(player->released, player);
		longitudinal(player->released, player, cub->exp);
		lateral(player->released, player, cub->exp);
		save_position(cub, player, cub->exp);
		printf("after anti px = %f >>> py = %f\n", player->x, player->y);
		printf("END ANTIGHOSTING\n");
	}
	return (0);
}
