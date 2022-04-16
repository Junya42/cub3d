/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:37:05 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 01:42:20 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_parse	parse;

	if (ac != 2)
		return (exit_parsing("Error in arguments\n"));
	if (parsing(av, &parse) == 1)
	{
		free_data(&parse);
		return (EXIT_FAILURE);
	}
	init_raycasting(&parse);
	return (EXIT_SUCCESS);
}
