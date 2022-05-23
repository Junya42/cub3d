/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:06:39 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/22 16:23:01 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	transparency(unsigned int color)
{
	if (color == 0xff00ff)
		return (0);
	return (1);
}

void	print_sprite(t_cub *cub, t_csp *s)
{
	s->x = s->sx;
	s->cx = 0;
	while (s->x < (s->sx + s->scale))
	{
		s->j = 0;
		s->cy = 0;
		s->index = (int)s->x >> 2;
		while (s->j < s->scale)
		{
			if (s->x > 0 && s->x < HRES && (s->sy + s->j) < VRES
				&& s->b > 0 && s->b < cub->zbuf[(int)s->index])
			{
				s->tmp = s->addr + ((int)(s->cy) % s->size
						* s->sizeline + (int)(s->cx) % s->size * (s->dbpp));
				s->color = *(unsigned int *)s->tmp;
				if (transparency(s->color))
					spxl_to_ray(cub, (int)s->x % HRES,
						(int)(s->sy + s->j) % VRES, s->color);
			}
			s->j += 1;
			s->cy += s->ncolor;
		}
		s->x += 1;
		s->cx += s->ncolor;
	}
}
