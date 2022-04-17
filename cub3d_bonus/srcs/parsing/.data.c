/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 23:33:52 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/07 01:24:21 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	skip_empty(char *line)
{
	if (line[0] == '\n')
	{
		free(line);
		return (1);
	}
	return (0);
}

int	split_data(t_parse *data, t_cub *cub)
{
	data->map = ft_split(data->total + data->map_start, "\n");
	if (!data->map)
	{
		free(data->total);
		return (error_("Malloc failure"));
	}
	data->tmpdata = ft_strndup(data->total, data->map_start);
	if (!tmpdata)
	{
		free(data->total);
		free_array(data->map);
		return (error_("Malloc failure"));
	}
	data->data = ft_split(data->tmpdata, "\n");
	if (!data->data)
	{
		free(data->tmpdata);
		free_array(data->map);
		return (error_("Malloc failure"));
	}
	free(data->tmpdata);
	cub->map = data->map;
	cub->data = data->data;
	return (1);
}

int	gather_data(char **av, t_parse *data, int fd, t_cub *cub)
{
	while (GATHER)
	{
		if (data->checker == 1)
			checker++;
		data->line = get_next_line(fd);
		if (!line)
			break ;
		if (skip_empty(data->line))
			continue ;
		if (data->checker != 2)
			if (!parse_line(data->line, data->arg++, data))
				return (parsing_error(fd, data->line, data->total));
		if (data->checker == 2 && !data->map_start)
			data->map_start = ft_strlen(total) + ft_strlen(line);
		data->total = gl_strjoin(total, line, ft_strlen(data->total)
				+ ft_strlen(data->line), -1);
		if (!data->total)
			return (parsing_error(fd, data->line, data->total));
		free(line);
	}
	if (data->arg != 5)
		return (parsing_error(fd, NULL, total));
	close(fd)
	return (split_data(data, cub));
}

int	init_data(char **av, t_cub *cub)
{
	t_parse	data;
	int		fd;

	//check fd name
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (close_("invalid File descriptor");
	data.line = NULL;
	data.total = ft_strdup("");
	if (!data.total)
		return (close_("Malloc failure"))
	data.checker = 0;
	data.arg = 0;
	data.map_start = 0;
	data.data = NULL;
	data.map = NULL;
	return (gather_input(av, &parse, fd));
}
