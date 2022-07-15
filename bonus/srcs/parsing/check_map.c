/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 03:36:45 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/17 22:40:43 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_char(char **map, char *set)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_charset(map[i][j], set) == 0)
				return (EXIT_FAILURE);
			if (is_charset(map[i][j], "NSEW") == 1)
				check++;
			j++;
		}
		i++;
	}
	if (check != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	closed_y(char **map, int x, int y)
{
	int	newy;
	int	check;

	newy = 0;
	check = 0;
	while (x > (int)ft_strlen(map[newy]))
		newy++;
	if (check_empty_char(map, x, y) == 1)
		return (EXIT_FAILURE);
	while (map[newy] && check != 2)
	{
		if (x < (int)ft_strlen(map[newy]))
		{
			if ((map[newy][x] == '1' || map[newy][x] == '3')
					&& newy < y)
				check = 1;
			else if ((map[newy][x] == '1' || map[newy][x] == '3')
					&& newy > y && check == 1)
				check = 2;
		}
		newy++;
	}
	if (check == 2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	closed_x(char **map, int x, int y)
{
	int	newx;
	int	check;

	newx = 0;
	check = 0;
	while (map[y][newx] && check != 2)
	{
		if ((map[y][newx] == '1' || map[y][newx] == '3') && newx < x)
			check = 1;
		else if ((map[y][newx] == '1' || map[y][newx] == '3')
				&& newx > x && check == 1)
			check = 2;
		newx++;
	}
	if (check == 2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_closed_wall(char **map, int x, int y)
{
	if (closed_x(map, x, y) == 0 && closed_y(map, x, y) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_wall(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_charset(map[i][j], CLOSED_VALID) == 1)
				if (check_closed_wall(map, j, i) == 1)
					return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
