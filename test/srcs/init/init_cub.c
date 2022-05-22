/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:58:02 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/22 15:34:39 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_ray	*alloc_ray(void)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->dra = deg_to_rad(0, FOV) / (HALFHRES >> 1);
	return (ray);
}

t_player	*alloc_player(t_cub *cub)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->dx = cub->cos * 5;
	player->dy = cub->sin * 5;
	player->angle = cub->a;
	player->released = 0;
	player->last_pressed = 0;
	player->input_fix = 0;
	player->ms = 1;
	player->x = cub->x;
	player->y = cub->y;
	player->safex = player->x;
	player->safey = player->y;
	return (player);
}

int	alloc_stuff(t_cub *cub)
{
	cub->player = NULL;
	cub->ray = NULL;
	cub->player = alloc_player(cub);
	cub->ray = alloc_ray();
	cub->id = -1;
	cub->sp_dist = 250;
	if (!cub->player || !cub->ray)
	{
		if (cub->player)
			free(cub->player);
		if (cub->ray)
			free(cub->ray);
		return (0);
	}
	return (1);
}

int	init_cub(t_cub *cub, t_parse *parse)
{
	cub->map = parse->map;
	get_map_xy(cub->map, cub);
	cub->cos = cos(cub->a);
	cub->sin = sin(cub->a);
	cub->end = 0;
	cub->z = 0;
	cub->ex = cub->mx << 6;
	cub->ey = cub->my << 6;
	cub->h = 0.25;
	cub->jump = 0;
	cub->brightness = 4;
	cub->flot = 0;
	cub->sz = 0;
	cub->z = 0;
	cub->door = 0;
	cub->doorcheck = 0;
	cub->degree = 0;
	cub->nb_sprites = 0;
	cub->lights = 0;
	cub->scroll = 0;
	if (alloc_stuff(cub) == 0)
		return (0);
	return (1);
}
