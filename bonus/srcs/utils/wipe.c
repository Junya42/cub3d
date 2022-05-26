/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:23:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/26 03:28:13 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_audio(t_cub *cub)
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
	Mix_CloseAudio();
	SDL_Quit();
	return (0);
}

void	free_sprites(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->nb_sprites)
	{
		j = 0;
		if (cub->sp[i].img)
			mlx_destroy_image(cub->mlx, cub->sp[i].img);
		if (cub->sp[i].animated == 1)
		{
			while (j < NB_FRAME)
			{
				if (cub->sp[i].anim[j].img)
					mlx_destroy_image(cub->mlx, cub->sp[i].anim[j].img);
				j++;
			}
		}
		i++;
	}
	free(cub->sp);
}

int	wipe_data(t_cub *cub, t_parse *parse)
{
	close_audio(cub);
	if (cub->text)
	{
		destroy_imgs(cub, cub->text);
		free(cub->text);
	}
	free_data(parse);
	free_array(cub->exp);
	free_array(cub->expl);
	free_array(cub->expr);
	free(cub->map_len);
	free(cub->ray);
	free(cub->player);
	free(cub->light);
	if (cub->sp)
		free_sprites(cub);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	if (cub->light)
		free_matrix(cub->chunk, cub->ey, cub->ex);
	return (0);
}
