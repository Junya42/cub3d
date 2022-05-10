/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:43:33 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/10 14:33:36 by cmarouf          ###   ########.fr       */
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

int	free_data(t_parse *p)
{
	if (p->npath)
		free(p->npath);
	if (p->spath)
		free(p->spath);
	if (p->wpath)
		free(p->wpath);
	if (p->epath)
		free(p->epath);
	if (p->map)
		free_array(p->map);
	return (0);
}
