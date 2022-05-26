/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:31:03 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/26 21:04:04 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_height_width(t_parse *parse, char **map)
{
	int	i;

	i = -1;
	parse->height = 0;
	while (map[++i])
		parse->height++;
	parse->width = malloc(sizeof(int) * parse->height);
	if (!parse->width)
		return ;
	i = -1;
	while (++i < parse->height)
		parse->width[i] = ft_strlen(map[i]);
}

void	get_expanded_height_width(t_cub *cub, char **map)
{
	int	i;

	i = -1;
	cub->map_height = 0;
	while (map[++i])
		cub->map_height++;
	cub->map_len = malloc(sizeof(int) * cub->map_height);
	if (!cub->map_len)
		return ;
	i = -1;
	while (++i < cub->map_height)
		cub->map_len[i] = ft_strlen(map[i]);
}
