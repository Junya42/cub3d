/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:50:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/13 19:06:03 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	change_sky(int keycode, t_cub *cub)
{
	if (keycode == '1' || keycode == 65436)
		cub->blue = 0;
	else if (keycode == '2' || keycode == 65433)
		cub->blue = 1;
}

void	adjust_minlight(int keycode, t_cub *cub)
{
	if (keycode == '4' || keycode == 65430)
		if (cub->ml > 0.05)
			cub->ml -= 0.01;
	if (keycode == '5' || keycode == 65437)
		if (cub->ml < 0.50)
			cub->ml += 0.01;
}

void	adjust_sky_light(int keycode, t_cub *cub)
{
	if (keycode == '7' || keycode == 65429)
		if (cub->r > 0.10)
			cub->r -= 0.01;
	if (keycode == '8' || keycode == 65431)
		if (cub->r < 1.00)
			cub->r += 0.01;
}

void	settings(int keycode, t_cub *cub)
{
	change_sky(keycode, cub);
	adjust_minlight(keycode, cub);
	adjust_sky_light(keycode, cub);
}
