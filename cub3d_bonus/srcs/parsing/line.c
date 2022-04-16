/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 01:05:00 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/07 01:24:41 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	skip_empty(char *line)
{
	if (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			return (1);
		}
	}
	return (0);
}

int	is_needle(char c, char *haystack)
{
	int	i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_comma(char *line)
{
	int	i;

}
