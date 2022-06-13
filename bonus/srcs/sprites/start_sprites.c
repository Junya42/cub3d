/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:22:24 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/13 20:13:32 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_sprite_txt(t_cub *cub, int i)
{
	get_nb_sprites(cub);
	if (create_sprites(cub) == 0)
		return (0);
	while (i < cub->nb_sprites)
	{
		cub->sp[i].type = search_type(cub);
		cub->sp[i].s_type = SPRITE;
		if (check_valid(cub->sp[i].type, LIGHTCODE))
				cub->sp[i].s_type = LIGHT;
		if (cub->sp[i].s_type == LIGHT)
			cub->lights++;
		cub->sp[i].index = 0;
		cub->sp[i].x = (float)cub->search_j * 64 + 32;
		cub->sp[i].y = (float)cub->search_i * 64 + 32;
		cub->sp[i].img = NULL;
		cub->sp[i].addr = NULL;
		cub->sp[i].csp.moveable = 0;
		if (give_sprite_texture(&cub->sp[i], cub) == 0)
			cub->sp_error = 0;
		cub->search_j++;
		i++;
	}
	return (cub->sp_error);
}
