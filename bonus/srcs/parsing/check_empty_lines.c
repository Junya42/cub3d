/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:37:54 by cmarouf           #+#    #+#             */
/*   Updated: 2022/06/18 17:10:00 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_line_up(char *str, int i, int check, int save)
{
	i = skip_new_line(i, str);
	while (str[i] && str[i] != '*')
	{
		if (str[i] != '\n' && check >= 2)
		{
			save = i;
			if (i == 0)
				i += 3;
			while (i && str[i] && str[i] != '\n')
			{
				printf("str[i] = %c\n", str[i]);
				if (is_charset(str[i], "NSEW0 "))
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
	while (str[i] && str[i] != '*')
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
				if (is_charset(str[i], "NSEW0 "))
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
