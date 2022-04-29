/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 05:14:37 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/17 16:29:40 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_direction(char *side, t_parse *p)
{
	if (ft_strncmp(side, "NO", 2) == 0 && p->check_ne == 0)
	{
		p->check_ne = 1;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(side, "SO", 2) == 0 && p->check_so == 0)
	{
		p->check_so = 1;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(side, "WE", 2) == 0 && p->check_we == 0)
	{
		p->check_we = 1;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(side, "EA", 2) == 0 && p->check_ea == 0)
	{
		p->check_ea = 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	check_texture_path(char *path)
{
	path[ft_strlen(path) - 1] = '\0';
	if (open(path, O_RDONLY) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_floor_ceilings(char *side, t_parse *p)
{
	if (ft_strncmp(side, "C", 1) == 0 && p->check_c == 0)
	{
		p->check_c = 1;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(side, "F", 1) == 0 && p->check_f == 0)
	{
		p->check_f = 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	check_rgb(char *code, int i)
{
	char	**range;

	range = NULL;
	range = ft_split(code, ',');
	if (!range)
		return (EXIT_FAILURE);
	if (!range[0] || !range[1] || !range[2] || range[3])
	{
		free_array(range);
		return (EXIT_FAILURE);
	}
	while (i < 3)
	{
		range[i][ft_strlen(range[i]) - 1] = '\0';
		if ((is_num(range[i]) == 1) || ft_atoi(range[i]) > 255
			|| ft_atoi(range[i]) < 0)
		{
			free_array(range);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free_array(range);
	return (EXIT_SUCCESS);
}

int	check_map_content(char **mcontent, t_parse *p)
{
	if (!mcontent[0] || check_direction(mcontent[0], p) == 0)
	{
		if (!mcontent[1] || check_texture_path(mcontent[1]) == 1)
			return (EXIT_FAILURE);
		gather_data(mcontent, p, TEXTURE);
		return (EXIT_SUCCESS);
	}
	else if (!mcontent[0] || check_floor_ceilings(mcontent[0], p) == 0)
	{
		if (!mcontent[1] || check_rgb(mcontent[1], 0) == 1)
			return (EXIT_FAILURE);
		gather_data(mcontent, p, RGB);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
