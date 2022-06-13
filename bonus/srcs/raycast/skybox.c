/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:09 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/07 17:34:30 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	pxl_skybox(t_cub *cub, int x, int y, int i)
{
	char	*tmp;
	t_text	*ptr;
	int		size;

	ptr = cub->text;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	size = (int)(y * ptr[i].size + x * (ptr[i].bpp / 8));
	if (size < 0 || y >= ptr[i].b)
		return (0xffffff);
	tmp = ptr[i].addr + size;
	return (*(unsigned int *)tmp);
}

void	get_skycolor(t_cub *cub, t_ray *ray, float fix_nra, float ra_to_pxl)
{
	if (!fix_nra)
		cub->scolor = pxl_skybox(cub, ray->i + HALFVRES + cub->z,
				(int)ra_to_pxl, 7);
	if (cub->blue)
		cub->scolor = colorize(cub->scolor, cub->r, cub->r, LCYAN);
	else
		cub->scolor = colorize(cub->scolor, cub->r, cub->r, LRED);
}

void	skybox(t_cub *cub, t_ray *ray)
{
	float	ra_to_pxl;
	float	fix_nra;
	float	endsky;

	ray->i = 0;
	fix_nra = 0;
	ra_to_pxl = secure_radians(ray->ra, cub->scroll) * 721;
	if (ra_to_pxl >= cub->text[7].b)
		fix_nra = 1;
	endsky = ((HALFVRES - cub->z) - (ray->diff) * (0.75 - cub->h));
	while (ray->i < endsky)
	{
		if (!cub->intro || cub->intro > 2)
		{
			if ((ray->i + HALFVRES + cub->z) >= cub->text[7].a)
				break ;
			get_skycolor(cub, ray, fix_nra, ra_to_pxl);
		}
		else
			cub->scolor = 0x000000;
		pxl_to_ray(cub, ray->nr, ray->i, cub->scolor);
		ray->i++;
	}
}

void	sky_reflection(t_cub *cub, t_ray *ray)
{
	ray->ra_sky = secure_radians(ray->ra, cub->scroll) * 721;
	if (cub->expr[(int)ray->ry][(int)ray->rx] != '1'
		&& (cub->intro == 0 || cub->intro > 3))
	{
		if (!adjacent_exp(cub, (int)ray->rx, (int)ray->ry, 32))
		{
			if (ray->ra_sky < cub->text[7].b
				&& ray->i + ray->ray < cub->text[7].a)
			{
				ray->color += shade(pxl_skybox(cub, ray->i + ray->ray,
							(int)ray->ra_sky, 7), 0.05);
				if (cub->blue)
					ray->color = colorize(ray->color, cub->r, cub->r, LCYAN);
				else
					ray->color = colorize(ray->color, cub->r, cub->r, LRED);
			}
		}
	}
}
