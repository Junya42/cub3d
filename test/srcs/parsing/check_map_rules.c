/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:53:54 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/22 16:06:08 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_map_rules(t_parse *p, char **map)
{
	if (check_char(map, VALID) == 1)
		return (EXIT_FAILURE);
	if (check_wall(map) == 1)
		return (EXIT_FAILURE);
	get_height_width(p, map);
	return (EXIT_SUCCESS);
}

static int	check_roof_rules(char **roof, t_parse *p)
{
	if (check_char_rf(roof, ROOF_VALID) == 1)
		return (EXIT_FAILURE);
	if (check_width_height("ROOF", roof, p) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_floor_rules(char **floor, t_parse *p)
{
	if (check_char_rf(floor, FLOOR_VALID) == 1)
		return (EXIT_FAILURE);
	if (check_width_height("FLOOR", floor, p) == 1)
		return (EXIT_FAILURE);
	if (check_wrong_placement(floor, p) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_all_rules(t_parse *p, char **rw_map)
{
	if (!rw_map[0] || !rw_map[1] || !rw_map[2] || rw_map[3])
		return (EXIT_FAILURE);
	p->map = ft_split(rw_map[0], '\n');
	if (!p->map)
		return (EXIT_FAILURE);
	p->roof = ft_split(rw_map[1], '\n');
	if (!p->map)
		return (EXIT_FAILURE);
	p->floor = ft_split(rw_map[2], '\n');
	if (!p->map)
		return (EXIT_FAILURE);
	if (check_map_rules(p, p->map) == 1)
		return (EXIT_FAILURE);
	if (check_roof_rules(p->roof, p) == 1)
		return (EXIT_FAILURE);
	if (check_floor_rules(p->floor, p) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
