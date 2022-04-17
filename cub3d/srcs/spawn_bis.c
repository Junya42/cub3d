/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:11:00 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:16:33 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	out_of_bound(char **map, int reach_y, int reach_x)
{
	int	x;

	x = 0;
	while (map[reach_y][x])
		x++;
	if (x < reach_x)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
