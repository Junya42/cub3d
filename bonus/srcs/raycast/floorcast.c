/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/13 19:19:48 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_ceiling(t_cast *c, t_cub *cub, t_ray *ray)
{
	c->color = 0;
	if (cub->h <= 0.25)
	{
		if (((Q)(ray->floor_y) >> 5) < cub->my
			&& ((Q)(ray->floor_x) >> 5) < cub->mx)
			if (((Q)(ray->floor_y) >> 5) > -1 && ((Q)(ray->floor_x) >> 5) > -1)
				if (cub->roof[((Q)(ray->floor_y) >> 5)]
						[((Q)(ray->floor_x) >> 5)] == '1')
					return (1);
	}
	else
	{
		if (((Q)(c->ceily) >> 5 < cub->my) && ((Q)(c->ceilx) >> 5) < cub->mx)
			if (((Q)(c->ceily) >> 5 > -1) && ((Q)(c->ceilx) >> 5) > -1)
				if (cub->roof[((Q)(c->ceily) >> 5)]
						[((Q)(c->ceilx) >> 5)] == '1')
					return (1);
	}
	if (!cub->intro || (cub->intro > 3))
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
	if (c->ceilcheck == 0 && (! cub->intro || cub->intro > 3) && cub->blue)
		c->color = colorize(c->color, cub->r, cub->r, LCYAN);
	else if (c->ceilcheck == 0 && (! cub->intro || cub->intro > 3)
		&& !cub->blue)
		c->color = colorize(c->color, cub->r, cub->r, LRED);
}

void	floor_light(t_cast *c, t_cub *cub, t_ray *ray)
{
	if (c->limiter < ray->raycast && (cub->intro == 0 || (cub->intro > 2)))
		c->color += shade(case_texture(cub, ray), cub->ml * cub->corrupt);
	if (!cub->intro || cub->intro >= 2)
	{
		c->color += pxl_from_img(cub, (int)ray->floor_y % cub->sfloor,
				(int)ray->floor_x % cub->sfloor, 6);
	}
	else
		c->color = 0x000000;
	ray->lx = (int)ray->floor_x * 2;
	ray->ly = (int)ray->floor_y * 2;
	if (!cub->intro)
	{
		c->flag = light(cub, cub->light, ray, cub->chunk);
		if (c->flag == 0)
			c->color = shade(c->color, cub->ml);
		else
			c->color = colorize(c->color, ray->shadow, ray->shadow, cub->hue);
	}
	pxl_to_ray(cub, ray->nr, ray->j, c->color);
}

void	ceiling_loop(t_cast *c, t_cub *cub, t_ray *ray)
{
	if (c->ceilcheck && (!cub->intro || (cub->intro >= 2)))
	{
		c->color = pxl_from_img(cub, (int)c->ceily % cub->sroof,
				(int)c->ceilx % cub->sroof, 9);
		if (!cub->intro)
		{
			if (c->flag == 0)
				c->color = shade(c->color, 0.05);
			else
				c->color = colorize(c->color, ray->shadow,
						ray->shadow - cub->sz / 5, cub->hue);
		}
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
