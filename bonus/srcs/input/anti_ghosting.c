/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_ghosting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:04:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/07 17:24:38 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_3d_sound(t_cub *cub, t_player *player)
{
	if (cub->mixing >= 4)
		cub->mixing = 0;
	cub->curr_time = timestamp();
	cub->sp_dist = cub->sp_dist * cub->blocked;
	if (cub->sp_dist > 250)
		cub->sp_dist = 250;
	Mix_SetPosition(1, (int)cub->sp_angle, cub->sp_dist);
	if (cub->curr_time - cub->time_move >= 300)
	{
		if (player->x == cub->lastx && player->y == cub->lasty)
		{
			Mix_FadeOutChannel(0, 200);
			cub->foot = 1;
		}
		else
		{
			cub->lastx = player->x;
			cub->lasty = player->y;
		}
	}
	if (Mix_Playing(0) == 0 && cub->foot != 1)
		Mix_PlayChannel(0, cub->foot_steps[cub->mixing], -1);
}

void	update_game_state(t_cub *cub, t_player *player)
{
	update_3d_sound(cub, player);
	jump(cub);
	if ((int)cub->y > -1 && (int)cub->x > -1
		&& (int)cub->y < cub->ey && (int)cub->x < cub->ex)
		open_door(cub, 0);
	raycast(cub, cub->ray);
	if (cub->pause == 1)
		floating(cub);
	animation(cub);
	sprite_casting(cub, cub->light);
	if (cub->warp == 1 && cub->brightness < 4)
	{
		if (cub->brightness + 0.2 == 4)
			cub->warp = 0;
		cub->brightness += 0.2;
	}
}

void	game(t_cub *cub, t_player *player)
{
	if (cub->corrupt < 30)
	{
		update_game_state(cub, player);
		display(cub, 0);
	}
}

int	anti_ghosting(t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (cub->end == 1 && !cub->exit)
	{
		outro_escape(cub, 0);
		mlx_destroy_window(cub->mlx, cub->win);
		return (0);
	}
	else if (cub->end == 1 && cub->exit)
		if (outro(cub))
			return (0);
	if (!player->last_pressed && player->input_fix && player->released)
	{
		usleep_(100000);
		rotate(player->released, cub, player);
		longitudinal(player->released, player, cub->exp, cub);
		lateral(player->released, player, cub->exp, cub);
		save_position(cub, player, cub->exp);
	}
	game(cub, player);
	if (!cub->end)
		cub->scroll = secure_radians(cub->scroll, SKY);
	return (0);
}
