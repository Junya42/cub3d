/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 00:16:22 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/12 11:20:04 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_cub_file(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i < 5)
		return (EXIT_FAILURE);
	if (filename[i - 1] == '\\' || filename[i - 1] == '/')
		return (EXIT_FAILURE);
	if (filename[i - 1] != 'b')
		return (EXIT_FAILURE);
	if (filename[i - 2] != 'u')
		return (EXIT_FAILURE);
	if (filename[i - 3] != 'c')
		return (EXIT_FAILURE);
	if (filename[i - 4] != '.')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	try_open_cub_file(char *filename, t_parse *parse)
{
	parse->fd = open(filename, O_RDONLY);
	if (parse->fd < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	init_parsing_variable(t_parse *p)
{
	p->buffer = NULL;
	p->mcontent = NULL;
	p->total = 0;
	p->check_ne = 0;
	p->check_so = 0;
	p->check_we = 0;
	p->check_ea = 0;
	p->check_c = 0;
	p->check_f = 0;
	p->npath = NULL;
	p->spath = NULL;
	p->wpath = NULL;
	p->epath = NULL;
	p->all_map = NULL;
	p->map = NULL;
	p->roof = NULL;
	p->floor = NULL;
	p->width = NULL;
	p->i = 0;
}

int	parsing(char **av, t_parse *parse)
{
	init_parsing_variable(parse);
	if (check_cub_file(av[1]) == 1)
		return (exit_parsing("Error in file\n"));
	if (try_open_cub_file(av[1], parse) == 1)
		return (exit_parsing("Error in file\n"));
	if (parse_data(parse) == 1)
		return (exit_parsing("Error in data parsing\n"));
	if (parse_map(parse, av[1]) == 1)
		return (exit_parsing("Error in map parsing\n"));
	return (1);
}
