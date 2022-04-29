/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/29 00:04:07 by anremiki         ###   ########.fr       */
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
		ray->curr_px = cub->x / 2 + cos(ray->ra) * 200 * 64 / ray->offj / fix;
		ray->next_px = cub->y / 2 + sin(ray->ra) * 200 * 64 / ray->offj / fix;
		color = pxl_from_img(cub, (int)ray->next_px % 64, (int)ray->curr_px % 64, 6);
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

void	floorcast(t_cub *cub, t_ray *ray)
{
	float			fix;
	unsigned int	color;
	float			distx;
	float			disty;
	int				jumpfix;
//	float			vx;
//	float			vy;
//	int				len;
//	int				nor;
//	float			stepx;
//	float			stepy;
//	float			xcpy;
//	float			ycpy;

	ray->j = ray->offset + ray->raycast;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	//if (ray->r == NRAY / 2)
//	{
//		xcpy = cub->x;
//		ycpy = cub->y;
//		vx = ray->rx - cub->x;
//		vy = ray->ry - cub->y;
//		len = sqrt(vx * vx + vy * vy);
//		stepx = vx / 10;
//		stepy = vy /10;
//		nor = (vx / len) * (vx / len) + (vy / len) * (vy / len);
//		printf("NEW FLOOR\n");
//		printf("x = %f >>> y = %f\n", cub->x, cub->y);
//		printf("rx = %f >>> ry = %f\n", ray->rx, ray->ry);
//		//printf("length sqrt = %f\n", sqrt(ray->rx * ray->rx + ray->ry * ray->ry));
//		printf("length sqrt = %d\n", len);
//		printf("stepx = %f\n", stepx);
//		printf("stepy = %f\n", stepy);
//		printf("normalized vector = %d\n", nor);
//		printf("ray lenght = %f\n", ray->ray);
//		for (int i = 0; i < 11; i++)
//		{
//			printf("x = %f\n", xcpy);
//			printf("y = %f\n", ycpy);
//			printf("\n");
//			xcpy += stepx;
//			ycpy += stepy;
//		}
//	}
	distx = cos(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	disty = sin(ray->ra) * 360 * (0.75 + cub->h) * 32 * (0.75 + cub->h);
	ray->offj = ray->j - (HALFVRES - cub->z);
	jumpfix = 0;
	if (cub->h < 0.25)
		jumpfix = 49;
	if (ray->r == NRAY / 2)
	{
		/*printf("\n		START		\n");
		printf("cub z = %f\n", cub->z);
		printf("raycast = %f\n", ray->raycast);
		printf("offset = %f\n", ray->offset);
		printf("j = %f\n", ray->offset + ray->raycast);
		printf("offj = %f\n", ray->offj);
		printf("height = %f\n", cub->h);
		printf("JUMPFIX = %d\n", jumpfix);*/
	}
	float heightfix = VRES;
	if (cub->z < 0)
		heightfix -= cub->z * 2;
	int	i = -1;
	float	lx = 288.0 - 64.0;
	float	ly = 416.0;
	float	len;
	float	dx;
	float	dy;
	float	lvl;
	float	max;
	int		limiter = 0;
	while (ray->j < heightfix)
	{
		ray->offj = ray->j - (HALFVRES - cub->z);
		ray->curr_px = cub->x / 2 + distx / ray->offj / fix;
		ray->next_px = cub->y / 2 + disty / ray->offj / fix;
		dx = ray->curr_px * 2 - lx;
		dy = ray->next_px * 2 - ly;
		len = sqrt(dx *dx + dy * dy);
		lvl = 0;
		int	blocked = 0;
		float	stepx = dx / 10; //100 = full precision
		float	stepy = dy / 10;
		float	dlx = lx + stepx;
		float	dly = ly + stepy;
		float	sx;
		float	sy;
		while (1)
		{
			sx = lx - dlx;
			sy = ly - dly;
			if (sqrt(sx * sx + sy * sy) >= len)
				break ;
			if (check_valid(cub->exp[(int)dly][(int)dlx], "12"))
			{
				blocked = 1;
				break ;
			}
			dlx += stepx;
			dly += stepy;
		}
		if (blocked == 0)
		{
			lvl = (1.0f / 230) * (230 - len * cub->sz);
			max = (1.0f / 230) * (230 - len);
			if (lvl > max)
				lvl = max;
		}
		//if (ray->r == NRAY / 2)
		//	printf("lvl = %f\n", cub->sz);
		color = pxl_from_img(cub, (int)ray->next_px % 64, (int)ray->curr_px % 64, 6);
		if (limiter < ray->raycast)
			color += case_texture(cub, ray);
		color = colorize(color, lvl, lvl, PURPLE);
		pxl_to_ray(cub, ray->nr, ray->j, color);
		if (cub->map[((int)(ray->next_px) >> 5)][((int)(ray->curr_px) >> 5)] == 32)
		{
			color = pxl_from_img(cub, (int)ray->next_px % 64, (int)ray->curr_px % 64, 5);
			color = colorize(color, lvl, lvl - cub->sz / 5, PURPLE);
			pxl_to_ray(cub, ray->nr, (int)(ray->offset - i), color);
		}
		/*if (cub->map[((int)(ray->next_px) >> 5)][((int)(ray->curr_px) >> 5)] == 32)
			if ((VRES - cub->z - (ray->j + cub->z) > 0))
				glass(cub, ray->nr, (VRES - cub->z - (ray->j + cub->z)), lvl);*/
			//glass(cub, ray->nr, (int)(ray->offset - i), lvl);
		ray->j++;
		i++;
		limiter++;
		ray->curr_px -= ray->next_px;
	}
	(void)jumpfix;
	/*if (ray->r == NRAY / 2)
	{
		printf("j = %d\n", ray->j);
		printf("heightfix = %f\n", heightfix);
		printf("VRES = %d\n", VRES);
	}*/
//	if (cub->exp[((int)(ray->ry - 1))][((int)(ray->rx - 1))] == 32 || cub->exp[((int)(ray->ry + 1))][((int)(ray->rx + 1))] == 32)
//		ceiling(cub, ray);
}

/*void	floorcast(t_cub *cub, t_ray *ray)
{
	float	target;
	float	fix;
	char	*addr;

	ray->j = ray->offset + ray->raycast;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	target = ray->j * (1024 * 32) + (32 * ray->r);
	addr = cub->rayaddr;
	while (ray->j < VRES)
	{
		float	ratio = 64 / (ray->j - HALFVRES);
		float	distance = (200 * ratio) * fix;
		float	x = distance * cos(ray->ra);
		float	y = distance * sin(ray->ra);

		x += cub->x;
		y += cub->y;
		
		int	cellx = (x / 64);
		int	celly = (y / 64);	

		if (ray->r == NRAY / 2)
		{
			printf("cellx : %d	celly : %d\n", cellx, celly);
		}
		if ((cellx < cub->mx) && (celly < cub->my) && (cellx > -1) && (celly > -1))
		{
			int	ximg = ((int)x % 64);
			int	yimg = ((int)y % 64);
			int	color = pxl_from_img(cub, ximg, yimg, 6);
			if (target > -1 && target < RES)
				*((unsigned int *)addr + (int)target) = color;
			target += (32 * 1024);
		}
		ray->j++;
	}
}*/
