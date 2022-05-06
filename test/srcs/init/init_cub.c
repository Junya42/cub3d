/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:58:02 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/06 00:42:33 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_sprite_txt(t_cub *cub)
{
	int	i;

	i = 0;
	get_nb_sprites(cub);
	if (create_sprites(cub) == 0)
		return (0);
	cub->search_j = 0;
	cub->search_i = 0;
	while (i < cub->nb_sprites)
	{
		cub->sp[i].type = search_type(cub);
		printf("sp[%d].type = %c\n", i, cub->sp[i].type);
		cub->sp[i].s_type = SPRITE;
		if (check_valid(cub->sp[i].type, "ULRGBCY"))
				cub->sp[i].s_type = LIGHT;
		if (cub->sp[i].s_type == LIGHT)
			cub->lights++;
		cub->sp[i].index = 0;
		cub->sp[i].x = (float)cub->search_j * 64 + 32;
		cub->sp[i].y = (float)cub->search_i * 64 + 32;
		if (cub->sp[i].s_type == LIGHT)
		{
			printf("sp[%d].x = %f\n", i, cub->sp[i].x);
			printf("sp[%d].x = %f\n", i, cub->sp[i].y);
		}
		cub->sp[i].img = NULL;
		cub->sp[i].addr = NULL;
		cub->sp[i].csp.moveable = 0;
		if (give_sprite_texture(&cub->sp[i], cub) == 0)
			return (0);
		cub->search_j++;
		i++;
	}
	printf("LIGHTS ============ %d\n", cub->lights);
	return (1);
}

t_ray *alloc_ray(void)
{
	t_ray *ray;

	ray = (t_ray *)malloc(sizeof(t_ray) * 1);
	if (!ray)
		return (NULL);
	ray->dra = deg_to_rad(0, FOV) / (HALFHRES >> 1);
	return (ray);
}

t_player *alloc_player(t_cub *cub)
{
	t_player *player;

	player = (t_player *)malloc(sizeof(t_player) * 1);
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

int	init_cub(t_cub *cub)
{
	int	check;

	check = 0;
	get_map_xy(cub->map, cub);
	cub->cos = cos(cub->a);
	cub->sin = sin(cub->a);
	cub->player = alloc_player(cub);
	if (!cub->player)
		check = 1;
	cub->ray = alloc_ray();
	if (!cub->ray)
		check += 2;
	if (check)
		return (check);
	cub->end = 0;
	cub->z = 0;
	cub->ex = cub->mx << 6;
	cub->ey = cub->my << 6;
	cub->h = 0.25;
	cub->jump = 0;
	cub->brightness = 4;
	cub->flot = 0;
	cub->sz = 0;
	cub->nb_sprites = 0;
	cub->lights = 0;
	return (0);
}
