/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:31:16 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/19 20:03:11 by cmarouf          ###   ########.fr       */
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
	if (ft_strncmp(mcontent[0], "C", 1) == 0)
	{
		return (C);
	}
	if (ft_strncmp(mcontent[0], "F", 1) == 0)
	{
		return (F);
	}
	return (NOTHING);
}

void	give_texture(t_parse *p, char **mcontent, int side)
{
	if (side == N)
	{
		p->npath = ft_strdup(mcontent[1]);
		return ;
	}
	if (side == S)
	{
		p->spath = ft_strdup(mcontent[1]);
		return ;
	}
	if (side == W)
	{
		p->wpath = ft_strdup(mcontent[1]);
		return ;
	}
	if (side == E)
	{
		p->epath = ft_strdup(mcontent[1]);
		return ;
	}
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
	int	side;

	side = which_side(mcontent);
	if (flag == TEXTURE)
	{
		if (side == N)
			return (give_texture(p, mcontent, N));
		if (side == S)
			return (give_texture(p, mcontent, S));
		if (side == W)
			return (give_texture(p, mcontent, W));
		if (side == E)
			return (give_texture(p, mcontent, E));
	}
	if (flag == RGB)
	{
		if (side == C)
			return (give_rgb(p, mcontent, C));
		if (side == F)
			return (give_rgb(p, mcontent, F));
	}
}
