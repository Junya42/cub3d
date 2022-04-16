/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:35:11 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/16 18:37:07 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	create_hooks(t_cub *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_handle, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, release, cub);
	mlx_hook(cub->win, 6, 0x40, mouse_rotation, cub);
}
