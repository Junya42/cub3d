/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:37:05 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/03 00:17:28 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (exit_parsing("Error in arguments\n"));
	if (parsing(av) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
