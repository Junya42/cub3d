/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:56:28 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/17 01:43:53 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fatal_error(char *str)
{
	write(STDERR, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

int	get_fd_size(char *filename)
{
	char	c;
	int		len;
	int		fd;

	len = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, &c, 1) > 0)
		len++;
	close(fd);
	return (len);
}

unsigned int	rgb_to_hex(unsigned int r, unsigned int g, unsigned int b)
{
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

void	free_mlx(t_ray *ray)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (ray->txt[i].img)
			mlx_destroy_image(ray->mlx, ray->txt[i].img);
		i++;
	}
	if (ray->img)
		mlx_destroy_image(ray->mlx, ray->img);
	if (ray->erase)
		mlx_destroy_image(ray->mlx, ray->erase);
	if (ray->mlx)
	{
		mlx_destroy_display(ray->mlx);
		free(ray->mlx);
	}
}
