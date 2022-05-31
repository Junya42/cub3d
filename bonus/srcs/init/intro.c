/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:48:17 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/31 13:41:38 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_intro(t_cub *cub, int update)
{
	cub->intro = update;
	cub->brightness = update;
}

void	intro(t_cub *cub, int i)
{
	cub->h = 1.50;
	cub->intro = 1;
	cub->brightness = 1;
	while (cub->intro)
	{
		raycast(cub, cub->ray);
		if (cub->h <= 0.25)
		{
			i++;
			cub->h = 0.25;
		}
		if (i > 100 && cub->intro == 1)
			update_intro(cub, 2);
		else if (i > 300 && cub->intro == 2)
			update_intro(cub, 3);
		else if (i > 500 && cub->intro == 3)
			update_intro(cub, 4);
		else if (i > 700)
			break ;
		cub->h -= 0.01;
		cub->scroll = secure_radians(cub->scroll, SKY);
		display(cub, 0);
	}
	cub->h = 0.25;
	cub->intro = 0;
}
