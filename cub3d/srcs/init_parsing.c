/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 00:16:22 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/15 04:04:38 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_cub_file(char *filename)
{
	int	i;

	i = ft_strlen(filename);
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

int	parsing(char **av, t_parse *parse)
{
	(void)parse;
	if (check_cub_file(av[1]) == 1)
		return (exit_parsing("Error in file\n"));
	if (try_open_cub_file(av[1], parse) == 1)
		return (exit_parsing("Error in file\n"));
	if (parse_data(parse) == 1)
		return (exit_parsing("Error in data parsing\n"));
	close(parse->fd);
	if (parse_map(parse, av[1]) == 1)
		return (exit_parsing("Error in map parsing\n"));
	return (EXIT_SUCCESS);
}
