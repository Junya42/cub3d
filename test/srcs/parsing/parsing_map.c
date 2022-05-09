/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:25:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/09 12:55:22 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_rules(char **map, char *to_free)
{
	free(to_free);
	if (check_char(map, VALID) == 1)
		return (EXIT_FAILURE);
	if (check_wall(map) == 1)
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
	close(p->fd);
	p->map = ft_split(str, '\n');
	if (!p->map)
	{
		free(str);
		return (EXIT_FAILURE);
	}
	if (check_rules(p->map, str) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
