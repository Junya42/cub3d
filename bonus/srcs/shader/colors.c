/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:36:06 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/01 16:31:03 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	red(unsigned int color, float shader)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (shader < 0)
		shader = 0;
	r = 0x000000;
	g = ((color >> 8) & 0x00ff);
	b = (color & 0x0000ff);
	color = ((0xff << 24) | ((r & 0xff) << 16)
			| ((g & 0xff) << 8) | (b & 0xff));
	return (color);
}

unsigned int	green(unsigned int color, float shader)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (shader < 0)
		shader = 0;
	r = (color >> 16);
	g = ((color >> 8) & 0x00ff) * shader;
	b = (color & 0x0000ff);
	color = ((0xff << 24) | ((r & 0xff) << 16)
			| ((g & 0xff) << 8) | (b & 0xff));
	return (color);
}

unsigned int	blue(unsigned int color, float shader)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (shader < 0)
		shader = 0;
	r = (color >> 16);
	g = ((color >> 8) & 0x00ff);
	b = (color & 0x0000ff) * shader;
	color = ((0xff << 24) | ((r & 0xff) << 16)
			| ((g & 0xff) << 8) | (b & 0xff));
	return (color);
}
