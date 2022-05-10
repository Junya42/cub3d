/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:01:58 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/10 14:50:34 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_game(t_cub *cub, t_parse *parse)
{
	int i;

	i = -1;
	while (++i < 4)
		if (cub->foot_steps[i])
			Mix_FreeChunk(cub->foot_steps[i]);
	if (cub->light_aura)
		Mix_FreeChunk(cub->light_aura);
	Mix_CloseAudio();
	SDL_Quit();
	free_mlx(cub);
	free_data(parse);
	return (0);
}

static inline void init_sound_null(t_cub *cub)
{
    cub->sp_dist = 0;
	cub->sp_angle = 0;
	cub->mixing = 0;
	cub->foot = 0;
	cub->curr_time = 0;
	cub->time_move = 0;
	cub->lastx = 0;
	cub->lasty = 0;
	cub->light_aura = NULL;
	cub->foot_steps[0] = NULL;
	cub->foot_steps[1] = NULL;
	cub->foot_steps[2] = NULL;
	cub->foot_steps[3] = NULL;
}

int	init_audio(t_cub *cub, int i)
{
	if (SDL_Init(SDL_INIT_AUDIO) == -1)
		return (0);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		return (0);
	init_sound_null(cub);
	cub->light_aura = Mix_LoadWAV("./Sound/ambiant_sound.wav");
	if (!cub->light_aura)
		return (0);
	cub->foot_steps[0] = Mix_LoadWAV("./Sound/allstep_1.wav");
	cub->foot_steps[1] = Mix_LoadWAV("./Sound/allstep_2.wav");
	cub->foot_steps[2] = Mix_LoadWAV("./Sound/allstep_3.wav");
	cub->foot_steps[3] = Mix_LoadWAV("./Sound/allstep_4.wav");
	while (++i < 4)
		if (!cub->foot_steps[i])
			return (0);
	Mix_FadeInChannel(1, cub->light_aura, -1, 3000);
	Mix_PlayChannel(0, cub->foot_steps[0], -1);
	Mix_Volume(0, 0);
	return (1);
}