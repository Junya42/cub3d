/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:43:33 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/03 16:55:43 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	exit_parsing(char *str)
{
	write(STDERR, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

void	show_parse_error(int arg, char *line)
{
	ft_printf("!ARG = %d\n", arg - 1);
	ft_printf("!Invalid parsing in line : %s\n", line);
}

void	free_string(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

char	*skip_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != 32)
		i++;
	if (line[i])
	{
		while (line[i] && line[i] == 32)
			i++;
		if (line[i])
			return (line + i);
	}
	return (line);
}
