/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:19:24 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/01 13:19:25 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	launch_game_loop(t_cub *cub)
{
	create_hooks(cub);
	mlx_loop_hook(cub->mlx, anti_ghosting, cub);
	mlx_loop(cub->mlx);
}

void	quit_game(t_cub *cub, t_parse *parse)
{
	wipe_data(cub, parse);
}

int	launch_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->win = mlx_new_window(cub->mlx, HRES, VRES, "cub3d");
	if (!cub->win)
		return (0);
	return (1);
}

int	load_game(t_cub *cub, t_parse *parse, char **av)
{
	if (parsing(av, parse) == 0)
		return (free_data(parse));
	if (launch_mlx(cub) == 0)
		return (free_data(parse));
	if (init_audio(cub, -1) == 0)
	{
		ft_putstr_fd("ERROR LOADING SOUNDS\n", STDERR);
		return (close_game(cub, parse));
	}
	if (init_cub(cub, parse) == 0)
		return (close_game(cub, parse));
	cub->blue = 0;
	if (create_window(cub, parse) == 0)
	{
		wipe_data(cub, parse);
		return (0);
	}
	cub->pause = 1;
	return (1);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	t_parse	parse;

	if (ac != 2)
		return (printf("\033[1;31mError\033[0m - Usage "
				": ./cub3d_bonus map_name\n"));
	if (load_game(&cub, &parse, av) == 0)
		return (1);
	launch_game_loop(&cub);
	quit_game(&cub, &parse);
	return (0);
}
