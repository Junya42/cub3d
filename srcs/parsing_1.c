/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 00:16:22 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/03 00:48:56 by cmarouf          ###   ########.fr       */
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

int	parsing(char **av)
{
	if (check_cub_file(av[1]) == 1)
		return (exit_parsing("Error in file\n"));
	return (EXIT_SUCCESS);
}
