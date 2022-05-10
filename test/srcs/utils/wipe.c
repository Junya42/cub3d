/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:23:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/10 12:45:25 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_sprites(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->nb_sprites)
	{
		j = 0;
		mlx_destroy_image(cub->mlx, cub->sp[i].img);
		while (j < NB_FRAME)
		{
			mlx_destroy_image(cub->mlx, cub->sp[i].anim[j].img);
			j++;
		}
		i++;
	}
	free(cub->sp);
}

int	wipe_data(t_cub *cub, t_parse *parse)
{
	destroy_imgs(cub, cub->text);
	free(cub->text);
	free_data(parse);
	free_array(cub->exp);
	free(cub->ray);
	free(cub->player);
	free(cub->light);
	free_sprites(cub);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free_matrix(cub->chunk, cub->ey, cub->ex);
	return (0);
}
