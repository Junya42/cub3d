/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:48:17 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/01 16:29:42 by anremiki         ###   ########.fr       */
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
		else if (i > 200 && cub->intro == 2)
			update_intro(cub, 3);
		else if (i > 300 && cub->intro == 3)
			update_intro(cub, 4);
		else if (i > 400)
			break ;
		cub->h -= 0.01;
		cub->scroll = secure_radians(cub->scroll, SKY);
		display(cub, 0);
	}
	cub->h = 0.25;
	cub->intro = 0;
}

void	outro_escape(t_cub *cub, int i)
{
	while (1)
	{
		raycast(cub, cub->ray);
		if (i > 100 && !cub->intro)
			cub->intro = 4;
		else if (i > 300 && cub->intro == 4)
			cub->intro = 3;
		else if (i > 500 && cub->intro == 3)
			cub->intro = 2;
		else if (i > 700 && cub->intro == 2)
			cub->intro = 1;
		cub->h -= 0.01;
		if (cub->h < -1)
			break ;
		cub->scroll = secure_radians(cub->scroll, -SKY);
		display(cub, 0);
		i++;
	}
}

int	outro(t_cub *cub)
{
	if (cub->corrupt == 1 && cub->end)
		cub->player->angle = secure_radians(cub->a, PI);
	cub->corrupt += 0.05;
	cub->r -= 0.01;
	cub->sz -= 0.030;
	if (cub->corrupt > 15)
		cub->lrange -= 10;
	cub->scroll = secure_radians(cub->scroll, -SKY);
	if (cub->corrupt > 30)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		return (1);
	}
	return (0);
}
