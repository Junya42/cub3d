/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:06:07 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/26 06:47:39 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static inline void init_sprite_var(t_cub *cub, t_csp *csp, int i)
{
	float	adjust;
	
	csp->j = 0;
	csp->size = cub->sp[i].size;
	csp->img = cub->sp[i].img;
	csp->addr = cub->sp[i].addr;
	csp->dbpp = cub->sp[i].dbpp;
	csp->sizeline = cub->sp[i].sizeline;
	csp->sx = cub->sp[i].x - cub->x;
	csp->sy = cub->sp[i].y - cub->y;
	csp->dist = sqrt((csp->sx * csp->sx) + (csp->sy * csp->sy));
	csp->a = (csp->sy * cub->cos) - (csp->sx * cub->sin);
	csp->b = (csp->sx * cub->cos) + (csp->sy * cub->sin);
	csp->scale = cub->sp[i].size * 80 / csp->b;
	adjust = (cub->h * 28 - 7);
	csp->sx = csp->a;	
	csp->sy = csp->b;
	csp->sx = (csp->sx * 1250.0 / csp->sy) + (HALFHRES);
	csp->sy = ((cub->sz + adjust) * 1250.0 / csp->sy) + (HALFVRES);
	csp->sy -= cub->z;
	if (csp->scale < 10)
		csp->scale = 10;
	csp->ncolor = cub->sp[i].size / csp->scale;
}

static inline void sort_sprite(t_sp *sp)
{
	int	i;
	t_sp ptr;

	i = 0;
	while (i + 1 < NB_SPRITE)
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

void    sprite_casting(t_cub *cub)
{
	int		i;

	i = 0;
	while (i < NB_SPRITE)
	{
		init_sprite_var(cub, &cub->sp[i].csp, i);
		i++;
	}
	sort_sprite(cub->sp);
	i = 0;
	while (i < NB_SPRITE)
	{
		if (cub->sp[i].csp.sx > -HRES  && cub->sp[i].csp.sx < HRES)
			print_sprite(cub, &cub->sp[i].csp);
		i++;
	}
}
