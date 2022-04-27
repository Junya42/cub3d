/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:36:06 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/26 00:51:37 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	red(int color, float shader)
{
	int	r;
	int	g;
	int	b;

	if (shader < 0)
		shader = 0;
	if (shader > 1)
		shader = 1;
	r = 0x000000;
	g = ((color >> 8) & 0x00ff);
	b = (color & 0x0000ff);
	color = ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
	if (color > 0xffffff)
		color = 0xffffff;
	return (color);
}

int	green(int color, float shader)
{
	int	r;
	int	g;
	int	b;

	if (shader < 0)
		shader = 0;
	if (shader > 1)
		shader = 1;
	r = (color >> 16);
	g = ((color >> 8) & 0x00ff) * shader;
	b = (color & 0x0000ff);
	color = ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
	if (color > 0xffffff)
		color = 0xffffff;
	return (color);
}

int	blue(int color, float shader)
{
	int	r;
	int	g;
	int	b;

	if (shader < 0)
		shader = 0;
	if (shader > 1)
		shader = 1;
	r = (color >> 16);
	g = ((color >> 8) & 0x00ff);
	b = (color & 0x0000ff) * shader;
	color = ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
	if (color > 0xffffff)
		color = 0xffffff;
	return (color);
}
