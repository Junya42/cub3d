/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:25:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/17 22:16:11 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_line_up(char *str, int i, int check, int save)
{
	i = skip_new_line(i, str);
	while (str[i])
	{
		if (str[i] != '\n' && check >= 2)
		{
			save = i;
			if (i == 0)
				i += 3;
			while (i && str[i] && str[i] != '\n')
			{
				if (!is_charset(str[i], "NSEW0 "))
					return (EXIT_FAILURE);
				i++;
			}
			i = save;
		}
		if (str[i] == '\n')
			check++;
		else
			check = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_line_down(char *str, int i, int check, int save)
{
	i = skip_new_line(i, str);
	while (str[i])
	{
		if (str[i] != '\n' && check >= 2)
		{
			save = i;
			if (i > 3)
				i -= 3;
			while (str[i] == '\n')
				i--;
			while (i && str[i] && str[i] != '\n')
			{
				if (!is_charset(str[i], "NSEW0 "))
					return (EXIT_FAILURE);
				i--;
			}
			i = save;
		}
		if (str[i] == '\n')
			check++;
		else
			check = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

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
	str = malloc(sizeof(char) * (size - p->size) + 1);
	if (!str)
		return (EXIT_FAILURE);
	end = read(p->fd, str, size - p->size);
	str[end] = '\0';
	if (check_line_down(str, 0, 0, 0) == 1 || check_line_up(str, 0, 0, 0) == 1)
	{
		free(str);
		return (EXIT_FAILURE);
	}
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
