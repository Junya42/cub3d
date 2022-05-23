/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:56:28 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/23 18:07:22 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_mlx(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}

void	init_struct_null(t_cub *cub)
{
	cub->text = NULL;
	cub->sp = NULL;
	cub->light = NULL;
	cub->expl = NULL;
	cub->expr = NULL;
}

void	init_null(t_cub *cub, t_text *t)
{
	int	i;

	i = -1;
	while (++i < 11)
	{
		t[i].img = NULL;
		t[i].addr = NULL;
	}
	cub->imap = NULL;
	cub->iray = NULL;
	cub->mapaddr = NULL;
	cub->rayaddr = NULL;
}
