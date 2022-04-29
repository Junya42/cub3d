/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 23:43:16 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/07 01:24:31 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parsing_error(int fd, char *line, char *total)
{
	if (line)
	{
		printf("Invalid parsing in line : %s\n", line);
		free(line);
	}
	else
		printf("Invalid parsing : More or less than 6 arguments\n");
	if (total)
		free(total);
	close(fd);
	return (0);
}

int	error_(char *error)
{
	printf("Error encountered : %s\n", error);
	return (0);
}

int	close_(char *error, int fd)
{
	close(fd);
	return (error_(error));
}
