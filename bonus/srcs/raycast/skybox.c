/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:09 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/01 15:54:21 by anremiki         ###   ########.fr       */
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
			if (!fix_nra)
				cub->scolor = pxl_skybox(cub, ray->i + HALFVRES + cub->z,
						(int)ra_to_pxl, 7);
			if (cub->blue)
				cub->scolor = colorize(cub->scolor, cub->r, cub->r, LCYAN);
			else
				cub->scolor = colorize(cub->scolor, cub->r, cub->r, LRED);
		}
		else
			cub->scolor = 0x000000;
		pxl_to_ray(cub, ray->nr, ray->i, cub->scolor);
		ray->i++;
	}
}
