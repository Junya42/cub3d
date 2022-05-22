/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:06:07 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/22 14:15:14 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static inline void set_texture_addr(t_cub *cub, t_csp *csp, int i)
{
	csp->size = cub->sp[i].size;
	csp->img = cub->sp[i].img;
	csp->addr = cub->sp[i].addr;
	csp->dbpp = cub->sp[i].dbpp;
	csp->sizeline = cub->sp[i].sizeline;
}

static inline void set_sound_value(t_cub *cub, t_csp *csp)
{
	if (csp->type == LIGHT)
	{
		cub->sp_dist = csp->dist;
		cub->sp_angle = atan2(csp->a, csp->b) * 180 / PI;
		if (cub->sp_angle < 0)
			cub->sp_angle += 360;
	}
}

static inline void init_sprite_var(t_cub *cub, t_csp *csp, int i)
{
	float	adjust;
	
	csp->j = 0;
	set_texture_addr(cub, csp, i);
	csp->sx = cub->sp[i].x - cub->x;
	csp->sy = cub->sp[i].y - cub->y;
	csp->a = (csp->sy * cub->cos) - (csp->sx * cub->sin);
	csp->b = (csp->sx * cub->cos) + (csp->sy * cub->sin);
	csp->dist = sqrt((csp->sx * csp->sx) + (csp->sy * csp->sy));
	set_sound_value(cub, csp);
	csp->scale = cub->sp[i].size * 80 / csp->b;
	adjust = (cub->h * 28 - 7);
	csp->sx = csp->a;	
	csp->sy = csp->b;
	csp->sx = (csp->sx * 1250.0 / csp->sy) + (HALFHRES);
	if (csp->moveable == 1)
		csp->sy = ((cub->sz + adjust) * 1250.0 / csp->sy) + (HALFVRES);
	else
		csp->sy = ((csp->z + adjust) * 1250.0 / csp->sy) + (HALFVRES);
	csp->sy -= cub->z;
	if (csp->scale < 10)
		csp->scale = 10;
	csp->ncolor = cub->sp[i].size / csp->scale;
}

static inline void sort_sprite(t_sp *sp, t_cub *cub)
{
	int	i;
	t_sp ptr;
	
	i = 0;
	while (i + 1 < cub->nb_sprites)
	{
		if (sp[i].csp.dist < sp[i + 1].csp.dist)
		{
			ptr = sp[i];
			sp[i] = sp[i + 1];
			sp[i + 1] = ptr;
		}
		i++;
	}
}

void	get_sound_id(t_cub *cub, t_light *lights, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub->lights)
	{
		if (lights[i].x == x && lights[i].y == y)
			break ;
		i++;
	}
	cub->id = lights[i].id;
	cub->ray->rx = (int)cub->x;
	cub->ray->ry = (int)cub->y;
	light(cub, lights, cub->ray, cub->chunk);
}

void    sprite_casting(t_cub *cub, t_light *light)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < cub->nb_sprites)
	{
		init_sprite_var(cub, &cub->sp[i].csp, i);
		i++;
	}
	sort_sprite(cub->sp, cub);
	i = 0;
	while (i < cub->nb_sprites)
	{
		if (cub->sp[i].csp.type == LIGHT)
			j = i;
		if (cub->sp[i].csp.sx > -HRES  && cub->sp[i].csp.sx < HRES)
			print_sprite(cub, &cub->sp[i].csp);
		i++;
	}
	get_sound_id(cub, light, cub->sp[j].x, cub->sp[j].y);
}