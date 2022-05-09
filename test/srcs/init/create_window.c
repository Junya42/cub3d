/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:03:50 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/09 18:25:33 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int init_erase_var(t_cub *cub)
{
    cub->erase = NULL;
    cub->erase = mlx_new_image(cub->mlx, HRES, VRES);
    if (!cub->erase)
         return (0);
    return (1);
}

int loading_screen(t_cub *cub, t_parse *parse)
{
    mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF, "Loading Sprites");
	if (!get_sprite_txt(cub, 0))
    {
        printf("ERROR LOADING SPRITES\n");
		return (0);
    }
	mlx_put_image_to_window(cub->mlx, cub->win, cub->erase , 0, 0);
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF, "Loading Chunks");
	cub->light = create_lights(cub, cub->sp);
    if (!cub->light)
    {
        printf("ERROR LOADING LIGHTS\n");
        return (0);
    }
	mlx_put_image_to_window(cub->mlx, cub->win, cub->erase , 0, 0);
	mlx_string_put(cub->mlx, cub->win, HALFHRES, HALFVRES, 0xFFFFFF, "Loading Textures");
	if (!create_imgs(cub, parse))
    {
        printf("ERROR LOADING TEXTURES\n");
		return (0);
    }
    return (1);
}

int	create_window(t_cub *cub, t_parse *parse)
{
    init_erase_var(cub);
    change_map(cub);
	cub->exp = expand(cub->map, cub->mx, cub->my, 64);
    if (loading_screen(cub, parse) == 0)
        return (0);
    if (cub->erase)
	    mlx_destroy_image(cub->mlx, cub->erase);
	return (1);
}