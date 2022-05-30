/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/30 18:09:56 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_ceiling(t_cast *c, t_cub *cub, t_ray *ray)
{
	c->color = 0;
	if (cub->h <= 0.25)
	{
		if (((q)(ray->floor_y) >> 5) < cub->my
			&& ((q)(ray->floor_x) >> 5) < cub->mx)
			if (((q)(ray->floor_y) >> 5) > -1 && ((q)(ray->floor_x) >> 5) > -1)
				if (cub->roof[((q)(ray->floor_y) >> 5)]
						[((q)(ray->floor_x) >> 5)] == '1')
					return (1);
	}
	else
	{
		if (((q)(c->ceily) >> 5 < cub->my) && ((q)(c->ceilx) >> 5) < cub->mx)
			if (((q)(c->ceily) >> 5 > -1) && ((q)(c->ceilx) >> 5) > -1)
				if (cub->roof[((q)(c->ceily) >> 5)]
						[((q)(c->ceilx) >> 5)] == '1')
					return (1);
	}
	if (c->ra_sky < cub->text[7].b
		&& (ray->j - (ray->offset + ray->raycast)) < cub->text[7].a)
		c->color = pxl_skybox(cub,
				ray->j - (ray->offset + ray->raycast) + HALFVRES,
				(int)c->ra_sky, 7);
	return (0);
}

void	update_maths(t_cast *c, t_cub *cub, t_ray *ray)
{
	ray->offj = ray->j - (HALFVRES - cub->z);
	ray->floor_x = cub->x / 2 + c->distx / ray->offj / c->fix;
	ray->floor_y = cub->y / 2 + c->disty / ray->offj / c->fix;
	c->ceilx = cub->x / 2 + c->dceilx / ray->offj / c->fix;
	c->ceily = cub->y / 2 + c->dceily / ray->offj / c->fix;
	c->ra_sky = secure_radians(ray->ra, cub->scroll) * 721;
	c->ceilcheck = check_ceiling(c, cub, ray);
}

void	floor_light(t_cast *c, t_cub *cub, t_ray *ray)
{
	if (c->limiter < ray->raycast)
		c->color += shade(case_texture(cub, ray), MINLIGHT);
	c->color += pxl_from_img(cub, (int)ray->floor_y % cub->sfloor,
			(int)ray->floor_x % cub->sfloor, 6);
	ray->lx = (int)ray->floor_x * 2;
	ray->ly = (int)ray->floor_y * 2;
	c->flag = light(cub, cub->light, ray, cub->chunk);
	if (c->flag == 0)
		c->color = shade(c->color, MINLIGHT);
	else
		c->color = colorize(c->color, ray->shadow, ray->shadow, cub->hue);
	pxl_to_ray(cub, ray->nr, ray->j, c->color);
}

void	ceiling_loop(t_cast *c, t_cub *cub, t_ray *ray)
{
	if (c->ceilcheck)
	{
		c->color = pxl_from_img(cub, (int)c->ceily % cub->sroof,
				(int)c->ceilx % cub->sroof, 9);
		if (c->flag == 0)
			c->color = shade(c->color, 0.05);
		else
			c->color = colorize(c->color, ray->shadow,
					ray->shadow - cub->sz / 5, cub->hue);
		pxl_to_ray(cub, ray->nr, (int)(ray->offset - c->i), c->color);
	}
	ray->j++;
	c->i++;
	c->limiter++;
	ray->curr_px -= ray->next_px;
}

void	floorcast(t_cub *cub, t_ray *ray)
{
	t_cast	c;

	init_floorcast(cub, ray, &c);
	while (ray->j < c.heightfix)
	{
		update_maths(&c, cub, ray);
		floor_light(&c, cub, ray);
		ceiling_loop(&c, cub, ray);
	}
}
