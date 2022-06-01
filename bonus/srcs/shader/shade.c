/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 05:13:38 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/01 16:31:19 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	shade(unsigned int color, float shader)
{
	int	r;
	int	g;
	int	b;

	if (shader < 0)
		shader = 0;
	r = ((color >> 16) & 0xff) * shader;
	g = ((color >> 8) & 0x00ff) * shader;
	b = (color & 0x0000ff) * shader;
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

unsigned int	addshade(unsigned int color, float shader)
{
	int	r;
	int	g;
	int	b;

	if (shader < 0)
		shader = 0;
	r = (color >> 16) * (shader / 2);
	g = ((color >> 8) & 0x00ff) * (shader / 2);
	b = (color & 0x0000ff) * (shader / 2);
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

unsigned int	colorize(unsigned int base, float shader, float dim, int color)
{
	if (color == LSHADE)
		return (shade(base, shader));
	base = shade(base, dim);
	if (color == LRED)
	{
		base = green(base, shader);
		base = blue(base, shader);
	}
	else if (color == LGREEN)
	{
		base = red(base, shader);
		base = blue(base, shader);
	}
	else if (color == LBLUE)
	{
		base = red(base, shader);
		base = green(base, shader);
	}
	else if (color == LCYAN)
		return (red(base, shader));
	else if (color == LPURPLE)
		return (green(base, shader));
	else if (color == LYELLOW)
		return (blue(base, shader));
	return (base);
}
