/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:01:58 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/18 16:25:47 by anremiki         ###   ########.fr       */
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
	if (cub->door_opening)
		Mix_FreeChunk(cub->door_opening);
	if (cub->teleportation)
		Mix_FreeChunk(cub->teleportation);
	if (cub->opening_theme)
		Mix_FreeMusic(cub->opening_theme);
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
	cub->teleportation = NULL;
	cub->door_opening = NULL;
	cub->opening_theme = NULL;
	cub->foot_steps[0] = NULL;
	cub->foot_steps[1] = NULL;
	cub->foot_steps[2] = NULL;
	cub->foot_steps[3] = NULL;
}

int	load_sound_path(t_cub *cub, int i)
{
	cub->light_aura = Mix_LoadWAV("./Sound/ambiant_sound.wav");
	if (!cub->light_aura)
		return (0);
	cub->door_opening = Mix_LoadWAV("./Sound/Door.wav");
	if (!cub->door_opening)
		return (0);
	cub->teleportation = Mix_LoadWAV("./Sound/TP2.wav");
	if (!cub->teleportation)
		return (0);
	cub->opening_theme = Mix_LoadMUS("./Sound/ab_theme2.wav");
	if (!cub->opening_theme)
	{
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
		return (0);
	}
	cub->foot_steps[0] = Mix_LoadWAV("./Sound/allstep_1.wav");
	cub->foot_steps[1] = Mix_LoadWAV("./Sound/allstep_2.wav");
	cub->foot_steps[2] = Mix_LoadWAV("./Sound/allstep_3.wav");
	cub->foot_steps[3] = Mix_LoadWAV("./Sound/allstep_4.wav");
	while (++i < 4)
		if (!cub->foot_steps[i])
			return (0);
	return (1);
}

int	init_audio(t_cub *cub, int i)
{
	cub->closed = 0;
	if (SDL_Init(SDL_INIT_AUDIO) == -1)
		return (0);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		return (0);
	init_sound_null(cub);
	if (load_sound_path(cub, i) == 0)
		return (0);
	
	Mix_VolumeMusic(12);
	Mix_VolumeChunk(cub->door_opening, 32);
	Mix_VolumeChunk(cub->teleportation, 64);
	//Mix_FadeInChannel(1, cub->light_aura, -1, 3000);
	Mix_PlayChannel(0, cub->foot_steps[0], -1);
	Mix_Volume(0, 0);
	return (1);
}
