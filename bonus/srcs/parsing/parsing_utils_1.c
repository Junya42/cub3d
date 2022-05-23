/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:43:33 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/23 20:02:55 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_parsing(char *str)
{
	write(STDERR, str, ft_strlen(str));
	return (0);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (EXIT_FAILURE);
	if (str[0] == '\n')
		return (EXIT_FAILURE);
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	free_and_return(t_parse *p, int flag, int exitcode)
{
	if (flag == 0)
	{
		if (p->buffer)
			free(p->buffer);
		if (p->mcontent)
			free_array(p->mcontent);
	}
	if (flag == 1)
		if (p->buffer)
			free(p->buffer);
	if (flag == 2)
		if (p->mcontent)
			free_array(p->mcontent);
	return (exitcode);
}

void	free_path(t_parse *p)
{
	if (p->npath)
		free(p->npath);
	if (p->spath)
		free(p->spath);
	if (p->wpath)
		free(p->wpath);
	if (p->epath)
		free(p->epath);
	if (p->o_path)
		free(p->o_path);
	if (p->r1_path)
		free(p->r1_path);
	if (p->r2_path)
		free(p->r2_path);
	if (p->f1_path)
		free(p->f1_path);
	if (p->f2_path)
		free(p->f2_path);
}

int	free_data(t_parse *p)
{
	free_path(p);
	if (p->map)
		free_array(p->map);
	if (p->floor)
		free_array(p->floor);
	if (p->roof)
		free_array(p->roof);
	if (p->width)
		free(p->width);
	if (p->all_map)
		free_array(p->all_map);
	return (0);
}
