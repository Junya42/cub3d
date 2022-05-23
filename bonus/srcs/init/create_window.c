/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:19:34 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/22 20:05:26 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_erase_var(t_cub *cub)
{
	cub->erase = NULL;
	cub->erase = mlx_new_image(cub->mlx, HRES, VRES);
	if (!cub->erase)
		return (0);
	return (1);
}

int	load_err(int exit_code, char *str)
{
	ft_putstr_fd(str, STDERR);
	return (exit_code);
}

int	loading_screen(t_cub *cub, t_parse *parse)
{
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF,
		"Loading Sprites");
	if (!get_sprite_txt(cub, 0))
		return (load_err(SPRITE_ERR, "ERROR LOADING SPRITES\n"));
	mlx_put_image_to_window(cub->mlx, cub->win, cub->erase, 0, 0);
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF,
		"Loading Chunks");
	cub->light = create_lights(cub, cub->sp);
	if (!cub->light)
		return (load_err(MATRIX_ERR, "ERROR LOADING LIGHTS\n"));
	mlx_put_image_to_window(cub->mlx, cub->win, cub->erase, 0, 0);
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF,
		"Loading Textures");
	if (!create_imgs(cub, parse))
		return (load_err(TEXTURE_ERR, "ERROR LOADING TEXTURES\n"));
	return (0);
}

int	create_window(t_cub *cub, t_parse *parse)
{
	init_erase_var(cub);
	init_struct_null(cub);
	change_map(cub);
	cub->exp = expand(cub->map, cub->mx, cub->my, 64);
	cub->roof = parse->roof;
	cub->floor = parse->floor;
	cub->expl = expand(cub->floor, cub->mx, cub->my, 64);
	cub->expr = expand(cub->roof, cub->mx, cub->my, 64);
	get_expanded_height_width(cub, cub->exp);
	cub->exit_code = loading_screen(cub, parse);
	if (cub->exit_code != 0)
	{
		if (cub->erase)
			mlx_destroy_image(cub->mlx, cub->erase);
		if (cub->win)
			mlx_destroy_window(cub->mlx, cub->win);
		return (0);
	}
	Mix_PlayMusic(cub->opening_theme, 0);
	Mix_FadeInChannel(1, cub->light_aura, -1, 3000);
	if (cub->erase)
		mlx_destroy_image(cub->mlx, cub->erase);
	return (1);
}
