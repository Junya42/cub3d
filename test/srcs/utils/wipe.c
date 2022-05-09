/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:23:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/09 18:47:55 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	wipe_data(t_cub *cub, t_parse *parse)
{
	(void)parse;
	destroy_imgs(cub, cub->text);
	mlx_destroy_display(cub->mlx);
	free_array(cub->map);
	free_array(cub->exp);
	return (0);
}
