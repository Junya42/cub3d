/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/23 08:24:15 by anremiki         ###   ########.fr       */
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

void	floorcast(t_cub *cub, t_ray *ray)
{
	float			fix;
	unsigned int	color;
	/*float			vx;
	float			vy;
	int				len;
	int				nor;
	float			stepx;
	float			stepy;
	float			xcpy;
	float			ycpy;
*/
	ray->j = ray->offset + ray->raycast;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	/*if (ray->r == NRAY / 2)
	{
		xcpy = cub->x;
		ycpy = cub->y;
		vx = ray->rx - cub->x;
		vy = ray->ry - cub->y;
		len = sqrt(vx * vx + vy * vy);
		stepx = vx / 10;
		stepy = vy /10;
		nor = (vx / len) * (vx / len) + (vy / len) * (vy / len);
		printf("NEW FLOOR\n");
		printf("x = %f >>> y = %f\n", cub->x, cub->y);
		printf("rx = %f >>> ry = %f\n", ray->rx, ray->ry);
		//printf("length sqrt = %f\n", sqrt(ray->rx * ray->rx + ray->ry * ray->ry));
		printf("length sqrt = %d\n", len);
		printf("stepx = %f\n", stepx);
		printf("stepy = %f\n", stepy);
		printf("normalized vector = %d\n", nor);
		printf("ray lenght = %f\n", ray->ray);
		for (int i = 0; i < 11; i++)
		{
			printf("x = %f\n", xcpy);
			printf("y = %f\n", ycpy);
			printf("\n");
			xcpy += stepx;
			ycpy += stepy;
		}
	}*/
	while (ray->j < VRES)
	{
		ray->offj = ray->j - (HALFVRES - cub->z);
		ray->curr_px = cub->x / 2 + cos(ray->ra) * 200 * 64 * (0.75 + cub->h) / ray->offj / fix;
		ray->next_px = cub->y / 2 + sin(ray->ra) * 200 * 64 * (0.75 + cub->h) / ray->offj / fix;
		/*if (ray->r == NRAY / 2)
		{
			printf("offj %f >>> ", ray->offj);
			printf("curr %f >>> ", ray->curr_px);
			printf("next %f\n", ray->next_px);
		}*/
		color = pxl_from_img(cub, (int)ray->next_px % 64, (int)ray->curr_px % 64, 6);
		pxl_to_ray(cub, ray->nr, ray->j, color);
		ray->j++;
	}
//	if (cub->exp[((int)(ray->ry - 1))][((int)(ray->rx - 1))] == 32 || cub->exp[((int)(ray->ry + 1))][((int)(ray->rx + 1))] == 32)
//		ceiling(cub, ray);
}
