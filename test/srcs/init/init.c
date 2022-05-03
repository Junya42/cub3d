/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 03:11:42 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/03 13:52:31 by anremiki         ###   ########.fr       */
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

int	create_window(t_cub *cub)
{
	void	*img;
	cub->z = -VRES;
	cub->scroll = 0;
	cub->mlx = NULL;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->win = mlx_new_window(cub->mlx, HRES, VRES, "cub3d");
	if (!cub->win)
		return (0);
	img = mlx_new_image(cub->mlx, HRES, VRES);
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF, "Loading Sprites");
	if (!get_sprite_txt(cub))
		return (0);
	mlx_put_image_to_window(cub->mlx, cub->win, img, 0, 0);
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF, "Loading Chunks");
	cub->light = create_lights(cub, cub->sp);
	mlx_put_image_to_window(cub->mlx, cub->win, img, 0, 0);
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF, "Loading Textures");
	if (!create_imgs(cub))
		return (0);
	mlx_destroy_image(cub->mlx, img);
	cub->z = 0;
	//while (cub->z < 4)
//	{
		//raycast(cub, cub->ray, 0);
//		cub->z += 2;
//	}*/
	cub->z = 0;
	//cub->nb_sprites = 0;
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
	p->i = 0;
}

int main(int ac, char **av)
{
	t_cub	cub;
	t_parse	parse;
	int		x;

	if (ac != 2)
		return (printf("\033[1;31mError\033[0m - Usage : ./cub3d_bonus map_name\n"));
	init_parsing_variable(&parse);
	if (parsing(av, &parse))
	{
		free_data(&parse);
		return (1);
	}
	cub.ray = NULL;
	cub.map = parse.map;
	x = init_cub(&cub);
	if (x)
	{
		printf("init cub = %d\n", x);
		return (0);
	}
	change_map(&cub);
	cub.exp = expand(cub.map, cub.mx, cub.my, 64);
	cub.z = 0;
	if (!create_window(&cub))
	{
		wipe_data(&cub);
		return (42);
	}
	create_hooks(&cub);
	printf("cub.x = %f	cub.y = %f\n", cub.x, cub.y);
	mlx_loop_hook(cub.mlx, anti_ghosting, &cub);
	mlx_loop(cub.mlx);
	mlx_destroy_display(cub.mlx);
	//wipe_data(&cub);
	return (0);
}
