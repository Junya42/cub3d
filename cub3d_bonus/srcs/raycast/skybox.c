/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:09 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/11 01:34:35 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skybox(t_cub *cub, t_ray *ray)
{
	float	ra_to_pxl;

	ra_to_pxl = ray->ra * 180 / PI;
	while (ray->i < ray->offset)
	{
		ray->color = pxl_from_img(cub, i, ra_to_pxl, 6);
		pxl_to_ray(cub, ray->nr, ray->i, ray->color);
		ray->i++;
	}
}
