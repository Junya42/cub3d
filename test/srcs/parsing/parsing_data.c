/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:41:53 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/29 03:38:19 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_variable(t_parse *p)
{
	p->buffer = NULL;
	p->mcontent = NULL;
	p->total = 0;
	p->check_ne = 0;
	p->check_so = 0;
	p->check_we = 0;
	p->check_ea = 0;
	p->check_c = 0;
	p->check_f = 0;
	p->npath = NULL;
	p->spath = NULL;
	p->wpath = NULL;
	p->epath = NULL;
	p->map = NULL;
}

int	malloc_error(t_parse *p)
{
	if (!p->npath)
		return (EXIT_FAILURE);
	if (!p->spath)
		return (EXIT_FAILURE);
	if (!p->wpath)
		return (EXIT_FAILURE);
	if (!p->epath)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_data(t_parse *p)
{
	while (42)
	{
		p->buffer = get_next_line(p->fd);
		if (!p->buffer)
		{
			free_and_return(p, 2, 0);
			break ;
		}
		if (p->buffer[0] == '#')
		{
			printf("COMMENT\n");
			free(p->buffer);
			continue ;
		}
		if (p->buffer[0] == '\n')
			printf("\n");
		else
			printf("ELSE\n");
		p->mcontent = ft_split(p->buffer, ' ');
		if (!p->mcontent)
			return (free_and_return(p, 1, EXIT_FAILURE));
		if (check_map_content(p->mcontent, p) == 0)
			p->total++;
		else if (p->buffer[0] != '\n')
			return (free_and_return(p, 0, EXIT_FAILURE));
		if (p->total == 6)
			break ;
		free_and_return(p, 0, 0);
	}
	if (malloc_error(p) == 1)
		return (free_and_return(p, 0, EXIT_FAILURE));
	return (free_and_return(p, 0, EXIT_SUCCESS));
}
