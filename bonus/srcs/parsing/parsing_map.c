/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:25:14 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/18 17:10:44 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_empty_line(char *str)
{
	free(str);
	return (EXIT_FAILURE);
}

int	check_map(t_parse *p)
{
	p->all_map = ft_split(p->str, '*');
	if (!p->all_map)
	{
		free(p->str);
		return (EXIT_FAILURE);
	}
	if (check_all_rules(p, p->all_map) == 1)
	{
		free(p->str);
		return (EXIT_FAILURE);
	}
	free(p->str);
	return (EXIT_SUCCESS);
}

int	parse_map(t_parse *p, char *fd_path)
{
	int		size;
	char	c;

	size = get_fd_size(p->fd, fd_path, 0);
	if (size <= 0)
		return (0);
	p->str = malloc(sizeof(char) * size + 1);
	if (!p->str)
		return (EXIT_FAILURE);
	while (read(p->fd, &c, 1) > 0)
	{
		if (c == '#')
			while (read(p->fd, &c, 1) > 0 && (c != '\n'))
				c = '\0';
		p->str[p->i] = c;
		p->i++;
	}
	p->str[size] = '\0';
	if (check_line_down(p->str, 0, 0, 0) == 1
		|| check_line_up(p->str, 0, 0, 0) == 1)
		return (exit_empty_line(p->str));
	if (check_map(p) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
