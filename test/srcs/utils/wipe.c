/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:23:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/10 15:57:41 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_audio(t_cub *cub)
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
		while (j < NB_FRAME)
		{
			if (cub->sp[i].anim[j].img)
				mlx_destroy_image(cub->mlx, cub->sp[i].anim[j].img);
			j++;
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
