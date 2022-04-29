/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:08:07 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/27 23:10:59 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	animation_light(t_sp *s)
{
	int	i;

	i = -1;
	s->animation[0] = "./imgs/tabdeath.xpm";
	s->animation[1] = "./imgs/tabdeath.xpm";
	s->animation[2] = "./imgs/tabdeath.xpm";
	s->animation[3] = "./imgs/tabdeath.xpm";
	s->animation[4] = "./imgs/tabdeath.xpm";
	s->animation[5] = "./imgs/tabdeath.xpm";
	s->animation[6] = "./imgs/tabdeath.xpm";
	s->animation[7] = "./imgs/tabdeath.xpm";
	while (++i < 8)
		if (open(s->animation[i], O_RDONLY) < 1)
			return (0);
	return (1);
}

int	txt_light(t_sp *sp, t_cub *cub)
{
	sp->img = mlx_xpm_file_to_image(cub->mlx, "./imgs/tabdeath.xpm", &sp->a, &sp->b);
	if (!sp->img)
		return (0);
	if (animation_light(sp) == 0)
		return (0);
	sp->csp.moveable = 1;
	sp->hue = SHADE;
	return (1);
}