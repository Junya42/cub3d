/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:31:16 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/30 23:25:42 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	which_side(char **mcontent)
{
	if (ft_strncmp(mcontent[0], "NO", 2) == 0)
		return (N);
	if (ft_strncmp(mcontent[0], "SO", 2) == 0)
		return (S);
	if (ft_strncmp(mcontent[0], "WE", 2) == 0)
		return (W);
	if (ft_strncmp(mcontent[0], "EA", 2) == 0)
		return (E);
	else
		return (bonus_side(mcontent));
	return (NOTHING);
}

void	give_texture(t_parse *p, char **mcontent, int side)
{
	if (side == N)
		p->npath = ft_strdup(mcontent[1]);
	else if (side == S)
		p->spath = ft_strdup(mcontent[1]);
	else if (side == W)
		p->wpath = ft_strdup(mcontent[1]);
	else if (side == E)
		p->epath = ft_strdup(mcontent[1]);
	else if (side == OW)
		p->o_path = ft_strdup(mcontent[1]);
	else if (side == F1)
		p->f1_path = ft_strdup(mcontent[1]);
	else if (side == F2)
		p->f2_path = ft_strdup(mcontent[1]);
	else if (side == R1)
		p->r1_path = ft_strdup(mcontent[1]);
	else if (side == R2)
		p->r2_path = ft_strdup(mcontent[1]);
}

unsigned int	get_hex_colors(char *code)
{
	char	**hex_code;
	int		r;
	int		g;
	int		b;

	hex_code = ft_split(code, ',');
	if (!hex_code)
		return (-1);
	r = ft_atoi(hex_code[0]);
	g = ft_atoi(hex_code[1]);
	b = ft_atoi(hex_code[2]);
	free_array(hex_code);
	return (rgb_to_hex(r, g, b));
}

void	give_rgb(t_parse *p, char **mcontent, int side)
{
	if (side == C)
	{
		p->colorc = get_hex_colors(mcontent[1]);
		return ;
	}
	if (side == F)
	{
		p->colorf = get_hex_colors(mcontent[1]);
		return ;
	}
}

void	gather_data(char **mcontent, t_parse *p, int flag)
{
	p->side = which_side(mcontent);
	if (flag == TEXTURE)
		return (give_texture(p, mcontent, p->side));
	if (flag == RGB)
		return (give_rgb(p, mcontent, p->side));
}
