/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:12:21 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/01 13:29:20 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	transform(char **map, int x, int y, char c)
{
	int	xmax;
	int	ymax;
	int	xsave;

	xsave = x;
	xmax = x + 64;
	ymax = y + 64;
	while (map[y] && y < ymax)
	{
		x = xsave;
		while (map[y][x] && x < xmax)
		{
			if (map[y][x] == 'D')
				map[y][x] = c;
			else
				map[y][x] = 'D';
			x++;
		}
		y++;
	}
}

int	init_expand(t_exp *c, int y, int mult)
{
	c->exp = NULL;
	c->exp = (char **)malloc(sizeof(char *) * (y * mult + 1));
	if (!c->exp)
		return (0);
	c->xcurs = 0;
	c->ycurs = 0;
	return (1);
}

void	fill_expand(char **map, t_exp *c, int x, int mult)
{
	while (c->ey < mult * (c->ycurs + 1))
	{
		c->exp[c->ey] = (char *)malloc(sizeof(char) * (x * mult + 1));
		c->xcurs = 0;
		while (map[c->ycurs][c->xcurs])
		{
			c->ex = mult * c->xcurs;
			while (c->ex < mult * (c->xcurs + 1))
			{
				c->exp[c->ey][c->ex] = map[c->ycurs][c->xcurs];
				c->ex++;
			}
			c->xcurs++;
		}
		c->exp[c->ey][c->ex] = '\0';
		c->ey++;
	}
}

char	**expand(char **map, int x, int y, int mult)
{
	t_exp	c;

	c.ey = 0;
	c.ex = 0;
	if (!init_expand(&c, y, mult))
		return (NULL);
	while (map[c.ycurs])
	{
		c.ey = mult * c.ycurs;
		fill_expand(map, &c, x, mult);
		c.ycurs++;
	}
	c.exp[c.ey] = 0;
	return (c.exp);
}
