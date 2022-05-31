/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:28:53 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/31 15:53:09 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_finding(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse->floor[i])
	{
		j = 0;
		while (parse->floor[i][j])
		{
			if (parse->floor[i][j] == 'K')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	pickup_key(t_cub *cub)
{
	if (cub->exit != 1)
	{
		cub->exit = 1;
		Mix_PlayChannel(4, cub->take_key, 0);
	}
}
