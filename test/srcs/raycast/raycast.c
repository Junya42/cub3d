/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:53:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/01 16:56:20 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reset_values(t_cub *cub, t_ray *ray)
{
	ray->i = 0;
	ray->limit = 0;
	ray->hray = 1000000;
	ray->vray = 1000000;
	ray->hdir = 0;
	ray->vdir = 0;
	ray->hx = cub->x;
	ray->hy = cub->y;
	ray->vx = cub->x;
	ray->vy = cub->y;
	ray->contan = (-1 / tan(ray->ra));
	ray->ntan = (-tan(ray->ra));
}

unsigned int	case_texture(t_cub *cub, t_ray *ray)
{
	if (ray->vray < ray->hray)
	{
		if (ray->vdir % 2)
			cub->dir = 1;
		else
			cub->dir = 2;
		return (vertical_texture(cub, ray, ray->vdir));
	}
	else
	{
		if (ray->hdir % 2)
			cub->dir = 3;
		else
			cub->dir = 4;
		return (horizon_texture(cub, ray, ray->hdir));
	}
}

void	dda_texture(t_ray *ray)
{
	if (ray->shadow > 1)
		ray->shadow = 1;
	ray->curr_px = ray->next_px * ray->off_px;
	ray->top = (int)ray->rx % 64;
	ray->bot = 64 - ray->top;
	ray->right = (int)ray->ry % 64;
	ray->left = 64 - ray->right;
	ray->nr = ray->r * 4;
}

int	dda(t_cub *cub, t_ray *ray)
{
	if (ray->hray < ray->vray)
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->ray = ray->hray;
	}
	if (ray->vray < ray->hray)
	{
		ray->ray = ray->vray;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
	}
	/*float	lx = 352.0;
	float	ly = 96.0 + 192.0;
	float	lx2 = 288.0 - 64;
	float	ly2 = 416.0;
	float	dx = ray->rx - lx;
	float	dy = ray->ry - ly;
	float	dx2 = ray->rx - lx2;
	float	dy2 = ray->ry - ly2;
//	float	px = lx - cub->x;
//	float	py = ly - cub->y;
//	float	plen = sqrt(px * px + py * py);
	float	len = sqrt(dx * dx + dy * dy);
	float	len2 = sqrt(dx2 * dx2 + dy2 * dy2);
	float	i = 0;
	float	i2 = 0;
	float	stepx = dx / 10;
	float	stepy = dy / 10;
	float	stepx2 = dx2 / 10;
	float	stepy2 = dy2 / 10;
	float	xl = lx + stepx;
	float	yl = ly + stepy;
	float	xl2 = lx2 + stepx2;
	float	yl2 = ly2 + stepy2;
	float	sx;
	float	sy;
	int		blocked = 0;
	int		blocked2 = 0;
	while (1)
	{
		sx = lx - xl;
		sy = ly - yl;
		if (sqrt(sx * sx + sy * sy) >= len - 10)
			break ;
		if (check_valid(cub->exp[(int)yl][(int)xl], "12"))
		{
			blocked = 1;
			break;
		}
		xl += stepx;
		yl += stepy;
	}
	while (1)
	{
		sx = lx2 - xl2;
		sy = ly2 - yl2;
		if (sqrt(sx * sx + sy * sy) >= len2 - 10)
			break ;
		if (check_valid(cub->exp[(int)yl2][(int)xl2], "12"))
		{
			blocked2 = 1;
			break;
		}
		xl2 += stepx2;
		yl2 += stepy2;
	}
	//float pal = acos((ray->ray * ray->ray + len * len - plen * plen) / (2 * ray->ray * len));
	float	max;
	if (blocked == 0)
	{
		i = (1.0f / 320) * (320 - len * cub->sz);
		max = (1.0f / 320) * (320 - len);
		if (i > max)
			i = max;
	}
	if (blocked2 == 0)
	{
		i2 = (1.0f / 230) * (230 - len2 * cub->sz);
		max = (1.0f / 230) * (230 - len2);
		if (i2 > max)
			i2 = max;
	}
	if (i < 0)
		i = 0;
	if (i2 < 0)
		i2 = 0;
	if (ray->r == NRAY / 2)
	{
		//printf("\ni %f >>> i2 %f\n", i, i2);
		//printf("LEN : len light mur = %f\n", len);
		//printf("\nRAY : len player mur = %f\n", ray->ray);
	//	printf(" PLEN : len player light = %f\n", plen);
	//	printf("ra = %f\n", ray->ra * 180 / PI);
	//	printf("i = %f\n", i);
	//	printf("degree player|WALL|light = %f\n", pal * 180 / PI);
	//	printf("degree wall|PLAYER|light = %f\n", cub->a * 180 / PI);
	//	printf("degree player|LIGHT|wall = %f\n", 180 - pal * 180 / PI - cub->a * 180 / PI);
	}
//	printf("ny %f >>> nx %f\n", ny, nx);*/
	ray->ray = fix_fisheye(cub->a, ray->ra, ray->ray);
	cub->zbuf[(int)ray->r] = ray->ray;
	ray->raycast = (64 * VRES / ray->ray);
	ray->next_px = 64 / ray->raycast;
	ray->off_px = 0;
	/*if (ray->raycast > VRES)
	{
		ray->off_px = (ray->raycast - VRES) / 2;
		ray->raycast = VRES;
	}*/
	ray->offset = ((HALFVRES - cub->z) - ray->raycast * (0.75 - cub->h));
	//ray->shadow = 2 / mysqrt(ray->ray) + i;
	//ray->shadow = i2 + i;
	ray->shadow = 1;
	if (ray->shadow > 1)
		ray->shadow = 1;
	//(void)lx;
//	(void)ly;
//	(void)i;
//	(void)len;
//	(void)plen;
//	(void)pal;
//	ray->l1 = i;
//	ray->l2 = i2;
//	if (i && i2)
//		return (3);
//	if (i)
//		return (2);
//	if (i2)
//		return (1);
	return (0);
}

void	raycast(t_cub *cub, t_ray *ray, int draw)
{
	(void)draw;
	init_ray(cub, ray);
	//mlx_put_image_to_window(cub->mlx, cub->win, cub->text[0].img, 0, 0);
	int	flag = 0;
	while (ray->r < NRAY)
	{
		reset_values(cub, ray);
		hray(cub, ray);
		ray->limit = 0;
		vray(cub, ray);
		flag = dda(cub, ray);
		dda_texture(ray);
		float	scale = ray->shadow / ray->raycast;
		float	dim = 0;
		int		lever = 0;
		while (ray->i < ray->raycast)
		{
			ray->color = case_texture(cub, ray);
			if (flag == 0)
			{
				ray->color = shade(ray->color, 1);
			}
			else
			{
				if (flag == 1)
					ray->color = colorize(ray->color, ray->shadow, dim, PURPLE);
				if (flag == 2)
					ray->color = colorize(ray->color, ray->shadow, dim, CYAN);
				if (flag == 3)
				{
					ray->color = colorize(ray->color, 1, dim, PURPLE);
					ray->color = colorize(ray->color, ray->shadow, dim, CYAN);
				}
			}
			pxl_to_ray(cub, ray->nr, (float)(int)(ray->i + ray->offset + draw), ray->color);
			ray->curr_px += ray->next_px;
			ray->i++;
			if (dim >= ray->shadow)
				lever = 1;
			if (lever)
				dim -= scale;
			else
				dim += scale;
		}
		//(void)dim;
		skybox(cub, ray);
		floorcast(cub, ray);
		ray->ra = secure_radians(ray->ra, ray->dra);
		ray->r++;
	}
	//display(cub, draw);
}
