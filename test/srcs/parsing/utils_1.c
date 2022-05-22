/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:56:28 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/22 16:04:44 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fatal_error(char *str)
{
	write(STDERR, str, ft_strlen(str));
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
