/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_light_yellow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:08:39 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/13 19:39:43 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_animation_light_yellow(t_sp *s)
{
	int	i;

	i = -1;
	s->anim_paths[0] = "./bonus/imgs/s_yellow/yellow0.xpm";
	s->anim_paths[1] = "./bonus/imgs/s_yellow/yellow1.xpm";
	s->anim_paths[2] = "./bonus/imgs/s_yellow/yellow2.xpm";
	s->anim_paths[3] = "./bonus/imgs/s_yellow/yellow3.xpm";
	s->anim_paths[4] = "./bonus/imgs/s_yellow/yellow4.xpm";
	s->anim_paths[5] = "./bonus/imgs/s_yellow/yellow5.xpm";
	s->anim_paths[6] = "./bonus/imgs/s_yellow/yellow6.xpm";
	s->anim_paths[7] = "./bonus/imgs/s_yellow/yellow7.xpm";
	while (++i < 8)
		if (open(s->anim_paths[i], O_RDONLY) < 1)
			return (0);
	return (1);
}

static int	gather_anim_frames(t_anim *anim, char *anim_path, t_cub *cub)
{
	anim->img = mlx_xpm_file_to_image(cub->mlx, anim_path,
			&anim->a, &anim->b);
	if (!anim->img)
		return (0);
	anim->addr = mlx_get_data_addr(anim->img, &anim->bpp,
			&anim->size, &anim->end);
	return (1);
}

static int	init_animation(t_sp *s, t_cub *cub, int flag)
{
	int	i;

	i = 0;
	while (i < NB_FRAME)
	{
		s->anim[i].img = NULL;
		s->anim[i].addr = NULL;
		i++;
	}
	i = 0;
	while (i < NB_FRAME && flag)
	{
		if (gather_anim_frames(&s->anim[i], s->anim_paths[i], cub) == 0)
			return (0);
		i++;
	}
	if (!flag)
		return (0);
	return (1);
}

int	txt_light_yellow(t_sp *sp, t_cub *cub)
{
	sp->img = NULL;
	sp->animated = 1;
	if (check_animation_light_yellow(sp) == 0)
		return (init_animation(sp, cub, 0));
	if (init_animation(sp, cub, 1) == 0)
		return (0);
	sp->img = mlx_xpm_file_to_image(cub->mlx,
			"./bonus/imgs/s_yellow/yellow0.xpm",
			&sp->a, &sp->b);
	if (!sp->img)
		return (0);
	sp->csp.moveable = 1;
	sp->hue = YELLOW;
	sp->csp.type = LIGHT;
	return (1);
}
