/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:41:53 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/03 17:17:58 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	init_check(t_parse *p)
{
	p->line = NULL;
	p->total = ft_strdup("");
	if (!p->total)
		return (fatal_error("Fatal "));
	p->checker = 0;
	p->arg = 0;
	p->map_start = 0;
	p->res = NULL;
	p->x = 0;
	return (EXIT_SUCCESS);
}

int	parse_arg(t_parse *p)
{
	if (p->checker != 2)
	{
		if (!parse_line(p->line, p->arg++))
		{
			show_parse_error(p->arg, p->line);
			free_string(p->line, p->total, NULL);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	start_check(t_parse *p)
{
	if (p->line[0] == 'C')
	{
		if (!p->map_start)
			p->map_start = ft_strlen(p->total) + ft_strlen(skip_line(p->line));
		p->checker++;
	}
	if (p->checker == 2)
		check_line(p->line);
	p->total = gl_strjoin(p->total, skip_line(p->line), ft_strlen(p->total)
			+ ft_strlen(skip_line(p->line)), -1);
	if (!p->total)
	{
		free_string(p->line, p->total, NULL);
		return (EXIT_FAILURE);
	}
	free(p->line);
	return (EXIT_SUCCESS);
}

int	gather_data(t_parse *p)
{
	p->res = ft_split(p->total + p->map_start, '\n');
	if (!p->res)
		return (fatal_error("Fatal "));
	printf("\n<------------------------>\n");
	while (p->res[p->x])
	{
		printf("res[%d] %s\n", p->x, p->res[p->x]);
		p->x++;
	}
	p->tmpdata = ft_strndup(p->total, p->map_start);
	if (!p->tmpdata)
	{
		free_array(p->res);
		return (fatal_error("Fatal "));
	}
	p->data = ft_split(p->tmpdata, '\n');
	if (!p->data)
	{
		free_array(p->res);
		free(p->tmpdata);
		return (fatal_error("Fatal "));
	}
	p->x = 0;
	printf("\n<------------------------>\n");
	while (p->data[p->x])
	{
		printf("data[%d] %s\n", p->x, p->data[p->x]);
		p->x++;
	}
	free_array(p->data);
	free_array(p->res);
	free(p->tmpdata);
	return (EXIT_SUCCESS);
}

int	check_valid_file(t_parse *p, int fd)
{
	if (init_check(p) == 1)
		return (EXIT_FAILURE);
	while (gnl_loop)
	{
		if (p->checker == 1)
			p->checker++;
		p->line = get_next_line(fd);
		if (!p->line)
			break ;
		if (p->line[0] == '\n')
		{
			free(p->line);
			continue ;
		}
		if (parse_arg(p) == 1)
			return (EXIT_FAILURE);
		if (start_check(p) == 1)
			return (EXIT_FAILURE);
	}
	if (gather_data(p) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
