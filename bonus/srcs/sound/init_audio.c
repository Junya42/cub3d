/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:01:58 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/31 15:29:43 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_sound_id(t_cub *cub, t_light *lights, float x, float y)
{
	int	i;

	i = 0;
	while (i < cub->lights)
	{
		if (lights[i].x == x && lights[i].y == y)
			break ;
		i++;
	}
	if (cub->lights != 0)
	{
		cub->id = lights[i].id;
		cub->ray->lx = (int)cub->x;
		cub->ray->ly = (int)cub->y;
		cub->blocked = 1.5;
		light(cub, lights, cub->ray, cub->chunk);
	}
}

int	close_game(t_cub *cub, t_parse *parse)
{
	int	i;

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
	if (cub->take_key)
		Mix_FreeChunk(cub->take_key);
	Mix_CloseAudio();
	SDL_Quit();
	free_mlx(cub);
	free_data(parse);
	return (0);
}

static inline void	init_sound_null(t_cub *cub)
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
	cub->take_key = NULL;
	cub->door_opening = NULL;
	cub->opening_theme = NULL;
	cub->foot_steps[0] = NULL;
	cub->foot_steps[1] = NULL;
	cub->foot_steps[2] = NULL;
	cub->foot_steps[3] = NULL;
}

int	load_sound_path(t_cub *cub, int i)
{
	cub->light_aura = Mix_LoadWAV("./bonus/Sound/ambiant_sound.wav");
	if (!cub->light_aura)
		return (0);
	cub->door_opening = Mix_LoadWAV("./bonus/Sound/Door.wav");
	if (!cub->door_opening)
		return (0);
	cub->teleportation = Mix_LoadWAV("./bonus/Sound/TP2.wav");
	if (!cub->teleportation)
		return (0);
	cub->opening_theme = Mix_LoadMUS("./bonus/Sound/ab_theme2.wav");
	if (!cub->opening_theme)
		return (0);
	cub->take_key = Mix_LoadWAV("./bonus/Sound/collectible.wav");
	if (!cub->take_key)
		return (0);
	cub->foot_steps[0] = Mix_LoadWAV("./bonus/Sound/allstep_1.wav");
	cub->foot_steps[1] = Mix_LoadWAV("./bonus/Sound/allstep_2.wav");
	cub->foot_steps[2] = Mix_LoadWAV("./bonus/Sound/allstep_3.wav");
	cub->foot_steps[3] = Mix_LoadWAV("./bonus/Sound/allstep_4.wav");
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
	Mix_PlayChannel(0, cub->foot_steps[0], -1);
	Mix_Volume(0, 0);
	return (1);
}
