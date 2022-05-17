/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:25:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/16 21:17:48 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_rules(t_parse *p, char **map)
{
	if (check_char(map, VALID) == 1)
		return (EXIT_FAILURE);
	if (check_wall(map) == 1)
		return (EXIT_FAILURE);
	get_height_width(p, map);
	return (EXIT_SUCCESS);
}

int	check_roof_rules(char **roof, t_parse *p)
{
	if (check_char_rf(roof, ROOF_VALID) == 1)
		return (EXIT_FAILURE);
	if (check_width_height("ROOF", roof, p) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_floor_rules(char **floor, t_parse *p)
{
	if (check_char_rf(floor, FLOOR_VALID) == 1)
		return (EXIT_FAILURE);
	if (check_width_height("FLOOR", floor, p) == 1)
		return (EXIT_FAILURE);
	if (check_wrong_placement(floor, p) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_all_rules(t_parse *p, char **rw_map, char *to_free)
{
	free(to_free);
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

int	parse_map(t_parse *p, char *fd_path)
{
	char	*str;
	int		size;
	char	c;

	size = get_fd_size(p->fd, fd_path, 0);
	if (size <= 0)
		return (0);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (EXIT_FAILURE);
	while (read(p->fd, &c, 1) > 0)
	{
		if (c == '#')
			while (read(p->fd, &c, 1) > 0 && (c != '\n'))
				c = '\0';
		str[p->i] = c;	
		p->i++;	
	}
	str[size] = '\0';
	p->all_map = ft_split(str, '*');
	if (!p->all_map)
	{
		free(str);
		return (EXIT_FAILURE);
	}
	if (check_all_rules(p, p->all_map, str) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
