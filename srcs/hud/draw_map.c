/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:10:22 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/11 22:10:24 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player(t_cub *cub, float x, float y)
{
	float	xmax;
	float	ymax;
	float	xsave;

	xmax = x + 7;
	ymax = y + 7;
	xsave = x;
	while (y < ymax)
	{
		x = xsave;
		while (x < xmax)
		{
			mlx_pixel_put(cub->mlx, cub->win, y, x, 0x7b00ff);
			x++;
		}
	}
}

int	get_offset(int x)
{
	int	offset;

	offset = 0;
	while (offset < 5)
	{
		if (x > 0)
			x--;
		else
			break ;
		offset++
	}
	return (offset);
}

int	get_new_value(int n)
{
	int	offset;

	offset = 0;
	while (offset < 5)
	{
		if (n > 0)
			n--;
		else
			break ;
		offset++
	}
	return (n);
}

unsigned int get_mapcolor(char c)
{
	if (c == '0')
		return (42);
	if (check_valid(c, "1PLlr"))
		return (0xbfbfbf);
	if (check_valid(c, "NSEW "))
		return (0x3575b5);
	return (0xba0047);
}

void	draw_index(t_cub *cub, int x, int y, char c)
{
	int				dx;
	int				dy;
	int				savey;

	if (c == '0')
		return ;
	dx = (x + 1) * 16 - 2;
	x = x * 16 + 2;
	dy = (y + 1) * 16 - 2;
	y = y * 16 + 2;
	savey = y;
	while (x < dx)
	{
		y = savey;
		while (y < dy)
		{
			if (!(y % 2))
				mlx_pixel_put(cub->mlx, cub->win, x, y, get_mapcolor(c));
			y++;
		}
		x++;
	}
}

void	draw_posmap(t_cub *cub, char **map, int x, int y)
{
	int	xmax;
	int	ymax;
	int	savex;
	int	offset;

	ymax = y + 5;
	xmax = x + 5;
	y = get_new_value(y);
	x = get_new_value(x);
	offset = get_offset(x);
	if (y < 0 || x < 0)
		return ;
	while (map[y] && y <= ymax)
	{
		x = xmax - 5 - offset;
		while (map[y][x] && x <= xmax)
		{
			draw_index(cub, x, y, map[y][x]);
			x++;
		}
		y++;
	}
}
