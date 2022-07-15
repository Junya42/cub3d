/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:42:19 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/17 22:15:20 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

int	skip_new_line(int i, char *str)
{
	while (str[i] == '\n')
		i++;
	return (i);
}

int	check_empty_char(char **map, int x, int y)
{
	if (map[y + 1])
	{
		if (x >= (int)ft_strlen(map[y + 1]))
			return (EXIT_FAILURE);
	}
	if (map[y - 1])
	{
		if (x >= (int)ft_strlen(map[y - 1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
