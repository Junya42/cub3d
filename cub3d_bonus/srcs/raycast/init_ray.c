/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:37:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 06:27:41 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_cub *cub, t_ray *ray)
{
	ray->rx = 0;
	ray->ry = 0;
	ray->xo = 0;
	ray->yo = 0;
	ray->ray = 0;
	ray->npy = (((int)cub->y >> 6) << 6);
	ray->npx = (((int)cub->x >> 6) << 6);
	ray->ra = cub->a - SCAN;
	ray->r = 0;
}
