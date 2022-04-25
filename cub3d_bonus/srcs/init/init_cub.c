/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:58:02 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/25 20:43:37 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_sprite_txt(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NB_SPRITE)
	{
		cub->sp[i].img = NULL;
		cub->sp[i].addr = NULL;
		i++;
	}
	printf("before texture sprite\n");
	cub->sp[0].img = mlx_xpm_file_to_image(cub->mlx,
			"./imgs/tabdeath.xpm", &cub->sp[0].a, &cub->sp[0].b);
	if (!cub->sp[0].img)
		return (0);
	printf("first texture sprite ok\n");
	cub->sp[0].addr = mlx_get_data_addr(cub->sp[0].img,
			&cub->sp[0].bpp, &cub->sp[0].sizeline,  &cub->sp[0].end);
	cub->sp[1].img = mlx_xpm_file_to_image(cub->mlx,
			"./imgs/light.xpm", &cub->sp[1].a, &cub->sp[1].b);
	if (!cub->sp[1].img)
		return (0);
	printf("second texture sprite ok\n");
	cub->sp[1].addr = mlx_get_data_addr(cub->sp[1].img,
			&cub->sp[1].bpp, &cub->sp[1].sizeline,  &cub->sp[1].end);
	cub->sp[0].dbpp = cub->sp[0].bpp >> 3;
	cub->sp[1].dbpp = cub->sp[1].bpp >> 3;
	cub->sp[0].size = 64;
	cub->sp[1].size = 64;
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

void	sprite_pos(t_cub *cub)
{
	cub->sp[0].x = 352.0;
	cub->sp[0].y = 288.0;
	cub->sp[1].x = 288.0 - 64;
	cub->sp[1].y = 416.0;
	cub->flot = 0;
	cub->sz = 0;
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
	sprite_pos(cub);
	return (0);
}
