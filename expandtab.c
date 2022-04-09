/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:12:21 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/10 00:47:06 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

/*char	**get_map(int ac, char **av)
{
	int fd;
	char	*file;
	char	*total;
	char	**map;

	fd = open(av[ac -1], O_RDONLY);
	if (fd < 0)
	{
		printf("wrong fd\n");
		return (NULL);
	}
	file = NULL;
	total = ft_strdup("");
	while (1)
	{
		file = get_next_line(fd);
		if (!file)
			break;
		total = gl_strjoin(total, file, ft_strlen(total) + ft_strlen(file), -1);
		free(file);
	}
	map = ft_split(total, '\n');
	if (total)
		free(total);
	return (map);
}

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

int	get_sizex(char **map)
{
	int	x;
	int	y;
	int	max;

	y = 0;
	max = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > max)
			max = x;
		y++;
	}
	return (max);
}

int	get_sizey(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}*/

char	**expand(char **map, int x, int y, int mult)
{
	char	**exp;
	int		xcurs;
	int		ycurs;
	int		ex;
	int		ey;

	exp = (char **)malloc(sizeof(char *) * (y * mult + 1));
	xcurs = 0;
	ycurs = 0;
	while (map[ycurs])
	{
		ey = mult * ycurs;
		while (ey < mult * (ycurs + 1))
		{
			exp[ey] = (char *)malloc(sizeof(char) * (x * mult + 1));
			xcurs = 0;
			while (map[ycurs][xcurs])
			{
				ex = mult * xcurs;
				while (ex < mult * (xcurs + 1))
				{
					exp[ey][ex] = map[ycurs][xcurs]; 
					ex++;
				}
				xcurs++;
			}
			exp[ey][ex] = '\0';
			ey++;
		}
		ycurs++;
	}
	exp[ey] = 0;
	return (exp);
}

//void	top_left_triangle(char **map, int mult, int x, int y);
//void	top_right_triangle(char **map, int mult, int x, int y);
//void	bot_left_triangle(char **map, int mult, int x, int y);
//void	bot_right_triangle(char **map, int mult, int x, int y);
void	circle(char **map, int mult, int x, int y)
{
	int	ymax;
	int	xmax;
	int	savex;
	int	savey;

	ymax = y + mult + 1;
	xmax = x + mult;
	savey = y;
	while (map[++y] && y < ymax)
	{
		x = xmax - mult;
		savex = x;
		while (map[y][x] && x < xmax)
		{
			if (y - savey == 0 || y - savey == mult - 1)
				if (x - savex < 3 || x - savex > 4)
					map[y][x] = '0';
			if (y - savey == 1 || y - savey == mult - 2)
				if (x - savex < 2 || x - savex > 5)
					map[y][x] = '0';
			if (y -savey == 2 || y - savey == mult - 3)
				if (x -savex < 1 || x - savex > 6)
					map[y][x] = '0';
			x++;
		}
	}
}

void	pillars(char **map, int mult, int x, int y)
{
	int	ymax;
	int	xmax;
	int	savey;
	int	savex;
	int	line;

	ymax = y + mult + 1;
	xmax = x + mult;
	savey = y;
	while (map[++y] && y < ymax)
	{
		x = xmax - mult;
		line = y - savey;
		savex = x;
		while (map[y][x] && x < xmax)
		{
			if (line > 1 && line < mult - 2)
				while (x < xmax)
					map[y][x++] = '0';
			if (x == xmax)
				break ;
			if (x  - savex > 1 && x - savex < mult - 2)
				map[y][x] = '0';
			x++;
		}
	}
}

void	left_pillars(char **map, int mult, int x, int y)
{
	int	ymax;
	int	xmax;
	int	savey;
	int	savex;
	int	line;

	ymax = y + mult + 1;
	xmax = x + mult;
	savey = y;
	while (map[++y] && y < ymax)
	{
		x = xmax - mult;
		line = y - savey;
		savex = x;
		while (map[y][x] && x < xmax)
		{
			if (line > 1 && line < mult - 2)
				while (x < xmax)
					map[y][x++] = '0';
			if (x == xmax)
				break ;
			if (x  - savex > 1)
				map[y][x] = '0';
			if (map[y][x] == 'l')
				map[y][x] = 'P';
			x++;
		}
	}
}

void	right_pillars(char **map, int mult, int x, int y)
{
	int	ymax;
	int	xmax;
	int	savey;
	int	savex;
	int	line;

	ymax = y + mult + 1;
	xmax = x + mult;
	savey = y;
	while (map[++y] && y < ymax)
	{
		x = xmax - mult;
		line = y - savey;
		savex = x;
		while (map[y][x] && x < xmax)
		{
			if (line > 1 && line < mult - 2)
				while (x < xmax)
					map[y][x++] = '0';
			if (x == xmax)
				break ;
			if (x - savex < mult - 2)
				map[y][x] = '0';
			if (map[y][x] == 'r')
				map[y][x] = 'P';
			x++;
		}
	}
}
//void	top_pillars(char **map, int mult, int x, int y);
//void	bot_pillars(char **map, int mult, int x, int y);

void	modify_map(char **map, char **exp, int mult)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'L')
				circle(exp, mult, x * mult, (y * mult) - 1);
			if (map[y][x] == 'P')
				pillars(exp, mult, x * mult, (y * mult) - 1);
			if (map[y][x] == 'l')
				left_pillars(exp, mult, x * mult, (y * mult) - 1);
			if (map[y][x] == 'r')
				right_pillars(exp, mult, x * mult, (y * mult) - 1);
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	char	**map;
	char	**expandmap;
	int	x;
	int	y;

	if (ac != 2)
		return (0);
	map = get_map(ac, av);
	printmap(map);
	y = get_sizey(map);
	x = get_sizex(map);
	printf("\n\n");
	//printf("\nx = %d > y = %d\n\n", x, y);
	expandmap = expand(map, x, y, 8);
	modify_map(map, expandmap, 8);
	printmap(expandmap);
	free_array(expandmap);
	free_array(map);
}
