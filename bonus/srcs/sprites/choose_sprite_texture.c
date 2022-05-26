/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sprite_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:36 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/26 03:28:01 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	give_sprite_var(t_sp *sp, t_cub *cub, char *path)
{
	sp->img = mlx_xpm_file_to_image(cub->mlx, path, &sp->a, &sp->b);
	if (!sp->img)
		return (0);
	sp->csp.moveable = 0;
	sp->animated = 0;
	sp->s_type = SPRITE;
	sp->csp.type = SPRITE;
	return (1);
}

int	choose_light_texture(t_sp *sp, t_cub *cub)
{
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

int	choose_sprite_texture(t_sp *sp, t_cub *cub)
{
	if (sp->type == 'P')
	{
		if (give_sprite_var(sp, cub, "./bonus/imgs/Human.xpm") == 0)
			return (0);
		sp->csp.moveable = 0;
		sp->animated = 0;
		sp->s_type = STATUE;
		sp->csp.type = STATUE;
		return (1);
	}
	else if (sp->type == 'K')
	{
		if (give_sprite_var(sp, cub, "./bonus/imgs/Key.xpm") == 0)
			return (0);
		sp->csp.moveable = 1;
		sp->animated = 0;
		sp->s_type = KEY;
		sp->csp.type = KEY;
		return (1);
	}
	else if (choose_light_texture(sp, cub) == 1)
		return (1);
	return (0);
}
