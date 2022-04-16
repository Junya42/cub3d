/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 03:11:42 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/16 20:40:04 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_cub(t_cub *cub)
{
	t_player	player;
	t_ray		ray;

	player.dx = cos(cub->a) * 5;
	player.dy = sin(cub->a) * 5;
	player.released = 0;
	player.last_pressed = 0;
	player.input_fix = 0;
	player.ms = 1;
	player.x = cub->x;
	player.y = cub->y;
	player.savex = player.x;
	player.savey = player.y;
	ray.dra = deg_to_rad(0, FOV) / (HALFHRES >> 1);
	cub->player = &player;
	cub->ray = &ray;
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
	{
		mlx_destroy_display(cub->mlx);
		return (0);
	}
	return (select(t_cub *cub));
}

int main(int ac, char **av)
{
	t_cub	cub;
	
	if (ac != 2)
		return (printf("\033[1;31mError\033[0m - Usage : ./cub3d_bonus map_name\n");
	init_cub(&cub);
	create_window(&cub);
	create_hooks(&cub);
	mlx_loop_hook(cub.mlx, antighosting, &cub);
	mlx_loop(cub.mlx);
	mlx_destroy_display(cub.mlx);
	wipe_data(cub);
	return (0);
}
