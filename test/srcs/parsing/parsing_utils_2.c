/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:42:19 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/22 16:42:10 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_door(char **map)
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
			if (map[i][j] == ' ')
				if (closed_door(i, j, map) == 1)
					return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);;
}

int	check_width_height(char *name, char **map, t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
		j++;
	if (j != p->height)
	{
		printf("HEIGHT ERROR ON %s, having %d should %d\n",
			name, j, p->height);
		return (EXIT_FAILURE);
	}
	while (i < p->height)
	{
		if ((int)ft_strlen(map[i]) != p->width[i])
		{
			printf("WIDTH ERROR ON %s, having %d should %d\n",
				name, (int)ft_strlen(map[i]), p->width[i]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_char_rf(char **map, char *set)
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
			if (is_charset(map[i][j], set) == 0)
			{
				printf("CHAR ERROR, having %c expected '%s'\n", map[i][j], set);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_wrong_placement(char **floor, t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (floor[i])
	{
		j = 0;
		while (floor[i][j])
		{
			if (is_charset(floor[i][j], SPRITE_VALID) == 1)
			{
				if (p->map[i][j] == '1' || p->map[i][j] == 'D'
					|| p->map[i][j] == '3')
					floor[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	is_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
