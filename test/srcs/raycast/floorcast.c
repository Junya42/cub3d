/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/20 13:32:19 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ceiling(t_cub *cub, t_ray *ray)
{
	float			fix;
	unsigned int	color;
	int				end;

	ray->j = ray->offset + ray->raycast;
	end = ray->offset;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	while (end >= 0)
	{
		ray->offj = ray->j - (HALFVRES - cub->z);
		ray->floor_x = cub->x / 2 + cos(ray->ra) * 200 * 64 / ray->offj / fix;
		ray->floor_y = cub->y / 2 + sin(ray->ra) * 200 * 64 / ray->offj / fix;
		color = pxl_from_img(cub, (int)ray->floor_y % 64, (int)ray->floor_x % 64, 6);
		pxl_to_ray(cub, ray->nr, end, color);
		end--;
		ray->j++;
	}
}

void	glass(t_cub *cub, float x, float y, float lvl)
{
	unsigned int	color;

	color = pxl_from_img(cub, x, y, -1);
	color = colorize(color, 0.55, 0.55, SHADE);
	pxl_to_ray(cub, (int)x, (int)y, color);
	(void)lvl;
}

void	init_floorcast(t_cub *cub, t_ray *ray, t_cast *c)
{
	ray->j = ray->offset + ray->raycast;
	c->fix = fix_fisheye(cub->a, ray->ra, 1);
	c->distx = cos(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	c->disty = sin(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	c->dceilx = cos(ray->ra) * 360 * 32 * (0.75 + cub->h);
	c->dceily = sin(ray->ra) * 360 * 32 * (0.75 + cub->h);
	ray->offj = ray->j - (HALFVRES - cub->z);
	c->heightfix = VRES;
	if (cub->z < 0)
		c->heightfix -= cub->z * 2;
	c->i = -1;
	c->limiter = 0;
}

int	check_ceiling(t_cast *c, t_cub *cub, t_ray *ray)
{
	c->color = 0;
	if (cub->h <= 0.25)
	{
		if (((int)(ray->floor_y) >> 5) > -1 && ((int)(ray->floor_x) >> 5) > -1)
			if (cub->roof[((int)(ray->floor_y) >> 5)][((int)(ray->floor_x) >> 5)] == '1')
				return (1);
	}
	else
	{
		if (((int)(c->ceily) >> 5 > -1) && ((int)(c->ceilx) >> 5) > - 1)
			if (cub->roof[((int)(c->ceily) >> 5)][((int)(c->ceilx) >> 5)] == '1')
				return (1);
	}
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
	c->color += pxl_from_img(cub, (int)ray->floor_y % 64,
			(int)ray->floor_x % 64, 6);
	ray->rx = (int)ray->floor_x * 2;
	ray->ry = (int)ray->floor_y * 2;
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
		if (cub->debug)
			printf("check on\n");
		c->color = pxl_from_img(cub, (int)c->ceily % 64,
				(int)c->ceilx % 64, 5);
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

/*void	floorcast(t_cub *cub, t_ray *ray)
{
	t_cast	c;

	init_floorcast(cub, ray, &c);
	while (ray->j < c.heightfix)
	{
		update_maths(&c, cub, ray);
		floor_light(&c, cub, ray);
		ceiling_loop(&c, cub, ray);
	}
}*/

void	floorcast(t_cub *cub, t_ray *ray)
{
	float			fix;
	unsigned int	color;
	float			distx;
	float			ceilx;
	float			ceily;
	float			ceil_x;
	float			ceil_y;
	float			disty;
	int				jumpfix;
	//t_cast			c;

	ray->j = ray->offset + ray->raycast;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	distx = cos(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	disty = sin(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	ceilx = cos(ray->ra) * 360 * 32 * (0.75 + cub->h);
	ceily = sin(ray->ra) * 360 * 32 * (0.75 + cub->h);
	if (cub->debug && ray->r == NRAY / 2)
	{
		printf("distX = %f\n", distx);
		printf("distY = %f\n", disty);
	}
	ray->offj = ray->j - (HALFVRES - cub->z);
	jumpfix = 0;
	if (cub->h < 0.25)
		jumpfix = 49;
	float heightfix = VRES;
	if (cub->z < 0)
		heightfix -= cub->z * 2;
	int	i = -1;
	int		limiter = 0;
	while (ray->j < heightfix)
	{
		ray->offj = ray->j - (HALFVRES - cub->z);
		ray->floor_x = cub->x / 2 + distx / ray->offj / fix;
		ray->floor_y = cub->y / 2 + disty / ray->offj / fix;
		ceil_x = cub->x / 2 + ceilx / ray->offj / fix;
		ceil_y = cub->y / 2 + ceily / ray->offj / fix;
		float	ra_sky = secure_radians(ray->ra, cub->scroll) * 721;
		int	ceilcheck = 0;
		//if (((int)(ray->floor_y -1 + (0.75 + cub->h)) >> 5) > -1 && ((int)(ray->floor_x -1 + (0.75 + cub->h)) >> 5) > -1)
		//	if (cub->roof[((int)(ray->floor_y -1 + (0.75 + cub->h)) >> 5)][((int)(ray->floor_x - 1 + (0.75 + cub->h)) >> 5)] == '1')
		if (((int)(ceil_y) >> 5 > -1) && ((int)(ceil_x) >> 5) > - 1)
			if (cub->roof[((int)(ceil_y) >> 5)][((int)(ceil_x) >> 5)] == '1')
				ceilcheck = 1;
		if (cub->debug && ray->r == NRAY / 2)
			if (((int)ray->floor_x >> 5) == (int)cub->x / 64 && ((int)ray->floor_y >> 5) == (int)cub->y / 64)
				printf("ceiling = %d\n", ceilcheck);
		if (!ceilcheck)
		{
			if (ra_sky < cub->text[7].b)
				cub->scolor = pxl_skybox(cub, ray->j - (ray->offset + ray->raycast) + HALFVRES, (int)ra_sky, 7);
			color = cub->scolor;
		}
		else
			color = 0;
		if (limiter < ray->raycast)
			color += shade(case_texture(cub, ray), MINLIGHT);
		color += pxl_from_img(cub, (int)ray->floor_y % 64, (int)ray->floor_x % 64, 6);
		//if (limiter < ray->raycast)
		//	color += case_texture(cub, ray);
		ray->rx = (int)ray->floor_x * 2;
		ray->ry = (int)ray->floor_y * 2;
		int flag = light(cub, cub->light, ray, cub->chunk);
		if (flag == 0)
			color = shade(color, MINLIGHT);
		else
			color = colorize(color, ray->shadow, ray->shadow, cub->hue);
		pxl_to_ray(cub, ray->nr, ray->j, color);
		if (ceilcheck)
		{
			//color = pxl_from_img(cub, (int)ray->floor_y % 64, (int)ray->floor_x % 64, 5);
			color = pxl_from_img(cub, (int)ceil_y % 64, (int)ceil_x % 64, 5);
			if (flag == 0)
				color = shade(color, 0.05);
			else
				color = colorize(color, ray->shadow, ray->shadow - cub->sz / 5, cub->hue);
			pxl_to_ray(cub, ray->nr, (int)(((ray->offset - i) - (0.75 + cub->h))), color);
			//pxl_to_ray(cub, ray->nr, VRES - ray->j, color);
		}
		//if (ceilcheck)
		//	glass(cub, ray->nr, (int)(ray->offset - i), MINLIGHT);
		//if (cub->map[((int)(ray->floor_y) >> 5)][((int)(ray->floor_x) >> 5)] == 32)
		  //if ((VRES - cub->z - (ray->j + cub->z) > 0))
		  //glass(cub, ray->nr, (VRES - cub->z - (ray->j + cub->z)), lvl);
		//glass(cub, ray->nr, (int)(ray->offset - i), lvl);
		ray->j++;
		i++;
		limiter++;
		ray->curr_px -= ray->next_px;
	}
	(void)jumpfix;
	(void)ceil_x;
	(void)ceil_y;
}
