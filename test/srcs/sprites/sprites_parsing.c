/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:03:41 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/30 18:51:08 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_sprites(t_cub *cub)
{
	cub->sp = (t_sp *)malloc(sizeof(t_sp) * cub->nb_sprites);
	if (!cub->sp)
		return (0);
	return (1);
}

void	get_nb_sprites(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (check_valid(cub->map[i][j], SPRITE_VALID) == 1)
				cub->nb_sprites++;
			j++;
		}
		i++;
	}
}

char	search_type(t_cub *c)
{
	while (c->map[c->search_i])
	{
        if (!c->map[c->search_i][c->search_j])
            c->search_j = 0;
		while (c->map[c->search_i][c->search_j])
		{
			if (check_valid(c->map[c->search_i][c->search_j], SPRITE_VALID) == 1)
				return (c->map[c->search_i][c->search_j]);
			c->search_j++;
		}
		c->search_i++;
	}
    return ('\0');
}

int	choose_sprite_texture(t_sp *sp, t_cub *cub)
{
	if (sp->type == 'P')
	{
		sp->img = mlx_xpm_file_to_image(cub->mlx, "./imgs/tabdeath.xpm", &sp->a, &sp->b);
		if (!sp->img)
			return (0);
		sp->csp.moveable = 0;
		sp->animated = 0;
		sp->s_type = PC;
		return (1);
	}
	if (sp->type == 'L')
		return (txt_light(sp, cub));
	if (sp->type == 'R')
		return (txt_light_red(sp, cub));
	if (sp->type == 'G')
		return (txt_light_green(sp, cub));
	if (sp->type == 'B')
		return (txt_light_blue(sp, cub));
	if (sp->type == 'C')
		return (txt_light_cyan(sp, cub));
	if (sp->type == 'U')
		return (txt_light_purple(sp, cub));
	if (sp->type == 'Y')
		return (txt_light_yellow(sp, cub));
	return (0);
}

int	give_sprite_texture(t_sp *sp, t_cub *cub)
{
	if (choose_sprite_texture(sp, cub) == 0)
		return (0);
	sp->addr = mlx_get_data_addr(sp->img, &sp->bpp, &sp->sizeline, &sp->end);
	sp->dbpp = sp->bpp >> 3;
	sp->size = 64;
	return (1);
}
