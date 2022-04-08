/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 03:11:42 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/07 03:28:05 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	ptr->win = mlx_new_window(cub->mlx, cub->wx, cub->wy, "cub3d");
	if (!ptr->win)
	{
		mlx_destroy_display(ptr->mlx);
		return (0);
	}
	return (select(t_cub *cub));
}

int main(int ac, char **av)
{
	t_cub		cub;
	
	if (ac != 1)
		return (printf("\033[1;31mError\033[0m - Usage : ./cub3d\n");
	init_cub(cub);
	create_window(cub);
	mlx_loop_hook(cub.mlx, antighosting, &cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, key_handle, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, release, &cub);
	mlx_loop(cub.mlx);
	mlx_destroy_display(cub.mlx);
	wipe_data(cub);
	return (0);
}
