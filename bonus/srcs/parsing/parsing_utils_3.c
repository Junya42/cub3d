/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:56:28 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/22 16:47:14 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fatal_error(char *str)
{
	write(STDERR, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

int	closed_door(int y, int x, char **map)
{
	if (map[y][x - 1] && map[y][x + 1])
		if (map[y][x + 1] == '1' && map[y][x - 1] == '1')
			return (EXIT_SUCCESS);
	if (map[y - 1][x] && map[y + 1][x])
		if (map[y + 1][x] == '1' && map[y - 1][x] == '1')
			return (EXIT_SUCCESS);
	ft_putstr_fd("DOOR IS NOT WELL CLOSED\n", STDERR);
	return (EXIT_FAILURE);
}

int	get_fd_size(int saved_fd, char *filename, int len)
{
	char	c;
	int		fd;
	int		where;

	where = lseek(saved_fd, 0, SEEK_CUR);
	if (where < 0)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (lseek(fd, where, SEEK_CUR) < 0)
	{
		close(fd);
		return (0);
	}
	while (read(fd, &c, 1) > 0)
	{
		if (c == '#')
			while (read(fd, &c, 1) > 0 && c != '\n')
				(void)c;
		len++;
	}
	close(fd);
	return (len);
}
