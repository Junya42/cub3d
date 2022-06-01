/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:11:43 by anremiki          #+#    #+#             */
/*   Updated: 2022/06/01 13:29:55 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	pxl_to_img(t_cub *cub, float x, float y, int i)
{
	char	*tmp;
	t_text	*ptr;

	ptr = cub->text;
	tmp = ptr[i].addr + (int)(y * ptr[i].size + x * (ptr[i].bpp / 8));
	*(unsigned int *)tmp = cub->color;
}

void	spxl_to_ray(t_cub *cub, float x, float y, unsigned int color)
{
	char	*tmp;
	int		size;

	if (!cub->rayaddr)
		return ;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0 && x)
		y = 0;
	size = (int)(y * cub->r_size + x * (cub->r_bpp / 8));
	if (size < 0 || size >= RES)
		return ;
	tmp = cub->rayaddr + size;
	*(unsigned int *)tmp = color;
}

void	pxl_to_ray(t_cub *cub, float x, float y, unsigned int color)
{
	char	*tmp;
	int		size;
	int		completer;

	if (!cub->rayaddr)
		return ;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0 && x)
		y = 0;
	size = (int)(y * cub->r_size + x * (cub->r_bpp / 8));
	if (size < 0 || size >= RES)
		return ;
	completer = 0;
	tmp = cub->rayaddr + size;
	while (completer < cub->brightness)
	{
		*((unsigned int *)tmp + completer) = color;
		completer++;
	}
}

unsigned int	pxl_from_img(t_cub *cub, int x, int y, int i)
{
	char	*tmp;
	t_text	*ptr;
	int		size;

	tmp = NULL;
	ptr = cub->text;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (i == -1)
	{
		size = (int)(y * cub->r_size + x * (cub->r_bpp / 8));
		if (size < 0 || size >= 220)
		tmp = cub->rayaddr + size;
	}
	else
	{
		size = (int)(y * ptr[i].size + x * (ptr[i].bpp / 8));
		if (size < 0 || size >= 1228800)
			return (0xffffff);
		tmp = ptr[i].addr + size;
	}
	return (*(unsigned int *)tmp);
}

unsigned int	rgb_to_hex(unsigned int r, unsigned int g, unsigned int b)
{
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}
