/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 03:11:42 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 07:14:27 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_angle(t_cub *cub, char dir)
{
	if (dir == 'N')
		cub->a = 4.71238;
	else if (dir == 'E')
		cub->a = 0;
	else if (dir == 'S')
		cub->a = PI / 2;
	else if (dir == 'W')
		cub->a = PI;
	else
		cub->a = 4.71238;
}

void    get_map_xy(char **map, t_cub *cub)
{
	int     y;
	int     x;
	int     max;

	y = 0;
	x = 0;
	max = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (check_valid(map[y][x], "NSEW"))
			{
				cub->x = x * 64 + 32;
				cub->y = y * 64 + 32;
				get_angle(cub, map[y][x]);
			}
			x++;
		}
		if (x > max)
			max = x;
		y++;
	}
	cub->mx = max;
	cub->my = y;
}

void	init_cub(t_cub *cub)
{
	t_player	player;
	t_ray		ray;

	get_map_xy(cub->map, cub);
	player.dx = cos(cub->a) * 5;
	player.dy = sin(cub->a) * 5;
	player.angle = cub->a;
	player.released = 0;
	player.last_pressed = 0;
	player.input_fix = 0;
	player.ms = 1;
	player.x = cub->x;
	player.y = cub->y;
	player.safex = player.x;
	player.safey = player.y;
	ray.dra = deg_to_rad(0, FOV) / (HALFHRES >> 1);
	cub->player = &player;
	cub->ray = &ray;
	cub->z = 1;
	cub->ex = cub->mx << 6;
	cub->ey = cub->my << 6;
}

int	create_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->win = mlx_new_window(cub->mlx, HRES, VRES, "cub3d");
	if (!cub->win)
		return (0);
	if (!create_imgs(cub))
		return (0);
	return (1);
}

void	init_parsing_variable(t_parse *p)
{
	p->buffer = NULL;
	p->mcontent = NULL;
	p->total = 0;
	p->check_ne = 0;
	p->check_so = 0;
	p->check_we = 0;
	p->check_ea = 0;
	p->check_c = 0;
	p->check_f = 0;
	p->npath = NULL;
	p->spath = NULL;
	p->wpath = NULL;
	p->epath = NULL;
	p->map = NULL;
}

int main(int ac, char **av)
{
	t_cub	cub;
	t_parse	parse;

	if (ac != 2)
		return (printf("\033[1;31mError\033[0m - Usage : ./cub3d_bonus map_name\n"));
	init_parsing_variable(&parse);
	if (parsing(av, &parse))
	{
		free_data(&parse);
		return (1);
	}
	cub.map = parse.map;
	init_cub(&cub);
	cub.exp = expand(cub.map, cub.mx, cub.my, 64);
	create_window(&cub);
	create_hooks(&cub);
	mlx_loop_hook(cub.mlx, anti_ghosting, &cub);
	mlx_loop(cub.mlx);
	mlx_destroy_display(cub.mlx);
	wipe_data(&cub);
	return (0);
}
