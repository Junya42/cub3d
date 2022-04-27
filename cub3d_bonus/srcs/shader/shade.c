/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 05:13:38 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/26 01:10:25 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


int shade(int color, float shader)
{
	int r;
	int g;
	int	b;

	if (shader < 0)
		shader = 0;
	if (shader > 1)
		shader = 1;
	r = (color >> 16) * shader;
	g = ((color >> 8) & 0x00ff) * shader;
	b = (color & 0x0000ff) * shader;
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

int addshade(int color, float shader)
{
	int r;
	int g;
	int	b;

	if (shader < 0)
		shader = 0;
	if (shader > 1)
		shader = 1;
	r = (color >> 16) * (shader / 2);
	g = ((color >> 8) & 0x00ff) * (shader / 2);
	b = (color & 0x0000ff) * (shader / 2);
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

int colorize(int base, float shader, float dim, int color)
{
	if (color == SHADE)
		return (shade(base, shader));
	base = shade(base, dim);
	if (color == RED)
	{
		base = green(base, shader);
		base = blue(base, shader);
	}
	else if (color == GREEN)
	{
		base = red(base, shader);
		base = blue(base, shader);
	}
	else if (color == BLUE)
	{
		base = red(base, shader);
		base = green(base, shader);
	}
	else if (color == CYAN)
		return (red(base, shader));
	else if (color == PURPLE)
		return (green(base, shader));
	else if (color == YELLOW)
		return (blue(base, shader));
	return (base);
}
