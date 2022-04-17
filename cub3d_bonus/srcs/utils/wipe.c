/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:23:45 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 02:02:34 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	wipe_data(t_cub *cub)
{
	destroy_imgs(cub, cub->text);
	free(cub->mlx);
	free_array(cub->map);
	free_array(cub->exp);
	return (0);
}
