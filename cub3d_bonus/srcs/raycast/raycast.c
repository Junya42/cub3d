/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:53:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/24 22:56:21 by anremiki         ###   ########.fr       */
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
			cub->dir = 1;
		else
			cub->dir = 2;
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

void	dda(t_cub *cub, t_ray *ray)
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
	float	lx = 352.0;
	float	ly = 288.0;
	float	dx = lx - ray->rx;
	float	dy = ly - ray->ry;
	float	px = lx - cub->x;
	float	py = ly - cub->y;
	float	plen = sqrt(px * px + py * py);
	float	len = sqrt(dx * dx + dy * dy);
	float	i;
	float pal = acos((ray->ray * ray->ray + len * len - plen * plen) / (2 * ray->ray * len));

	i = (1.0f / 250) * (250 - len);
	if (ray->r == NRAY / 2)
	{
		printf("\nRAY : len player mur = %f\n", ray->ray);
		printf(" PLEN : len player light = %f\n", plen);
		printf("LEN : len light mur = %f\n", len);
		printf("ra = %f\n", ray->ra * 180 / PI);
		printf("i = %f\n", i);
		printf("degree player|WALL|light = %f\n", pal * 180 / PI);
		printf("degree wall|PLAYER|light = %f\n", cub->a * 180 / PI);
		printf("degree player|LIGHT|wall = %f\n", 180 - pal * 180 / PI - cub->a * 180 / PI);
	}
//	printf("ny %f >>> nx %f\n", ny, nx);
	ray->ray = fix_fisheye(cub->a, ray->ra, ray->ray);
	ray->raycast = (64 * VRES / ray->ray);
	ray->next_px = 64 / ray->raycast;
	ray->off_px = 0;
	if (ray->raycast > VRES)
	{
		ray->off_px = (ray->raycast - VRES) / 2;
		ray->raycast = VRES;
	}
	ray->offset = ((HALFVRES - cub->z) - ray->raycast * (0.75 - cub->h));
	//ray->shadow = 2 / mysqrt(ray->ray) + i;
	ray->shadow = i;
	if (ray->shadow > 1)
		ray->shadow = 1;
	(void)lx;
	(void)ly;
	(void)i;
	(void)len;
	(void)plen;
}

void	raycast(t_cub *cub, t_ray *ray, int draw)
{
	init_ray(cub, ray);
	//mlx_put_image_to_window(cub->mlx, cub->win, cub->text[0].img, 0, 0);
	while (ray->r < NRAY)
	{
		reset_values(cub, ray);
		hray(cub, ray);
		ray->limit = 0;
		vray(cub, ray);
		dda(cub, ray);
		dda_texture(ray);
		while (ray->i < ray->raycast)
		{
			ray->color = case_texture(cub, ray);
			pxl_to_ray(cub, ray->nr, (float)(int)(ray->i + ray->offset + draw), ray->color);
			ray->curr_px += ray->next_px;
			ray->i++;
		}
		skybox(cub, ray);
		floorcast(cub, ray);
		ray->ra = secure_radians(ray->ra, ray->dra);
		ray->r++;
	}
	display(cub, draw);
}
