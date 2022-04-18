/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:09 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/18 16:08:26 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skybox(t_cub *cub, t_ray *ray)
{
	float	ra_to_pxl;

	ray->i = 0;
	while (ray->i < ray->offset)
	{
		ra_to_pxl = ray->ra * (180 / PI);
		ray->color = pxl_from_img(cub, ray->i, (int)ra_to_pxl, 7);
		pxl_to_ray(cub, ray->nr, ray->i, ray->color);
		ray->i++;
	}
}
