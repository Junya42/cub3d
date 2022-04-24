/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:09 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/22 06:59:47 by anremiki         ###   ########.fr       */
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
	if (size < 0 || y >= 1280)
		return (0xffffff);
	tmp = ptr[i].addr + size;
	return (*(unsigned int *)tmp);
}

void	skybox(t_cub *cub, t_ray *ray)
{
	float	ra_to_pxl;
	float	fix_nra;

	ray->i = 0;
	fix_nra = 0;
	ra_to_pxl = ray->ra * 360 - cub->scroll;
	if (ra_to_pxl >= 1280)
		fix_nra = 1;
	while (ray->i < ray->offset)
	{
		//ra_to_pxl = ray->ra * (180 / PI);
		if (!fix_nra)
			cub->color = pxl_skybox(cub, ray->i, (int)ra_to_pxl, 7);
		else
			cub->color = pxl_skybox(cub, ray->i, (int)ra_to_pxl - 1280, 10);
		if (cub->color == 0xffffff)
		{
	//		printf("rapxl = %f\n", ra_to_pxl);
			break;
		}
		pxl_to_ray(cub, ray->nr, ray->i, cub->color);
		ray->i++;
	}
}
