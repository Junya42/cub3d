/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:42:19 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/03 17:19:01 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	check_valid(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_comma(char *line)
{
	int	i;

	i = 0;
	if (line[i] == ',')
		return (0);
	while (line[i])
	{
		if (line[i] == ',' && !check_valid(line[i + 1], "0123456789"))
			return (0);
		i++;
	}
	return (1);
}

int	check_num(char *line)
{
	int		i;
	int		j;
	int		checker;

	i = 0;
	checker = 0;
	while (line[i] && line[i] == 32)
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	j = i;
	while (line[i] && line[i] != '\n')
	{
		if (!check_valid(line[i], "0123456789,"))
			return (0);
		if (line[i] == ',')
			checker++;
		i++;
	}
	if (checker == 2)
		return (check_comma(line + j));
	return (0);
}

int	check_path(char *line, int arg)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 2;
	fd = -1;
	if (arg < 4)
	{
		while (line[i] && line[i] == 32)
			i++;
		if (line[i])
		{
			tmp = ft_strdup(&line[i]);
			if (!tmp)
				return (0);
			tmp[ft_strlen(tmp) - 1] = '\0';
			fd = open(tmp, O_RDONLY);
			free(tmp);
		}
		if (fd < 0 || !line[i])
			return (close_fd(fd, line, i, 0));
	}
	else
		return (check_num(line + 2));
	return (close_fd(fd, line, 0, 1));
}

int	parse_line(char *line, int arg)
{
	if (arg == 0)
		if (ft_strncmp(line, "NO ", 3) != 0)
			return (0);
	if (arg == 1)
		if (ft_strncmp(line, "SO ", 3) != 0)
			return (0);
	if (arg == 2)
		if (ft_strncmp(line, "WE ", 3) != 0)
			return (0);
	if (arg == 3)
		if (ft_strncmp(line, "EA ", 3) != 0)
			return (0);
	if (arg == 4)
		if (ft_strncmp(line, "F ", 2) != 0)
			return (0);
	if (arg == 5)
		if (ft_strncmp(line, "C ", 2) != 0)
			return (0);
	return (check_path(line, arg));
}
