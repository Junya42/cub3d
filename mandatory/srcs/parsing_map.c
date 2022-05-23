/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:25:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/16 20:51:39 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_rules(char **map, char *to_free)
{
	free(to_free);
	if (check_char(map, "NSEW01 ") == 1)
		return (EXIT_FAILURE);
	if (check_wall(map) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_map(t_parse *p, char *filename)
{
	char	*str;
	int		end;
	int		size;

	size = get_fd_size(filename);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (EXIT_FAILURE);
	if (try_open_cub_file(filename, p) == 1)
		return (EXIT_FAILURE);
	end = read(p->fd, str, size);
	str[end] = '\0';
	p->map = ft_split(str, '\n');
	if (!p->map)
	{
		free(str);
		return (EXIT_FAILURE);
	}
	if (check_rules(p->map + 6, str) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
