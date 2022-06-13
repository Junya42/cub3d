/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sprite_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:36 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/13 20:14:39 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	give_sprite_var(t_sp *sp, t_cub *cub, char *path)
{
	sp->img = mlx_xpm_file_to_image(cub->mlx, path, &sp->a, &sp->b);
	if (!sp->img)
		return (0);
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
		sp->csp.moveable = 0;
		sp->animated = 0;
		sp->s_type = STATUE;
		sp->csp.type = STATUE;
		if (give_sprite_var(sp, cub, "./bonus/imgs/Human.xpm") == 0)
			return (0);
		return (1);
	}
	else if (sp->type == 'K')
	{
		sp->csp.moveable = 1;
		sp->animated = 0;
		sp->s_type = KEY;
		sp->csp.type = KEY;
		if (give_sprite_var(sp, cub, "./bonus/imgs/Key.xpm") == 0)
			return (0);
		return (1);
	}
	else if (choose_light_texture(sp, cub) == 1)
		return (1);
	return (0);
}
