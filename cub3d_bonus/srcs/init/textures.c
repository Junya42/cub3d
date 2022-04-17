/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:30:53 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 01:55:15 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	addr(t_cub *cub, t_text *t, char *(*add)(void *, int *, int *, int *))
{
	int	i;

	i = -1;
	t[0].addr = (*add)(t[0].img, &t[0].bpp, &t[0].size, &t[0].end);
	t[1].addr = (*add)(t[1].img, &t[1].bpp, &t[1].size, &t[1].end);
	t[2].addr = (*add)(t[2].img, &t[2].bpp, &t[2].size, &t[2].end);
	t[3].addr = (*add)(t[3].img, &t[3].bpp, &t[3].size, &t[3].end);
	t[4].addr = (*add)(t[4].img, &t[4].bpp, &t[4].size, &t[4].end);
	t[5].addr = (*add)(t[5].img, &t[5].bpp, &t[5].size, &t[5].end);
	t[6].addr = (*add)(t[6].img, &t[6].bpp, &t[6].size, &t[6].end);
	t[7].addr = (*add)(t[7].img, &t[7].bpp, &t[7].size, &t[7].end);
	t[8].addr = (*add)(t[8].img, &t[8].bpp, &t[8].size, &t[8].end);
	t[9].addr = (*add)(t[9].img, &t[9].bpp, &t[9].size, &t[9].end);
	while (++i < 10)
		if (!t[i].addr)
			return (0);
	cub->mapaddr = (*add)(cub->imap, &cub->m_bpp, &cub->m_size, &cub->m_end);
	cub->rayaddr = (*add)(cub->iray, &cub->r_bpp, &cub->r_size, &cub->r_end);
	if (!cub->mapaddr || !cub->rayaddr)
		return (0);
	return (1);
}

int	imgs(t_cub *cub, t_text *t, void *(*xpm)(void *, char *, int *, int *))
{
	int	i;

	i = -1;
	t[0].img = (*xpm)(cub->mlx, "./imgs/bookshelf.xpm", &t[0].a, &t[0].b);
	t[1].img = (*xpm)(cub->mlx, "./imgs/birch_planks.xpm", &t[1].a, &t[1].b);
	t[2].img = (*xpm)(cub->mlx, "./imgs/blackstone.xpm", &t[2].a, &t[2].b);
	t[3].img = (*xpm)(cub->mlx, "./imgs/bricks.xpm", &t[3].a, &t[3].b);
	t[4].img = (*xpm)(cub->mlx, "./imgs/pblackstone.xpm", &t[4].a, &t[4].b);
	t[5].img = (*xpm)(cub->mlx, "./imgs/doomfloor.xpm", &t[5].a, &t[5].b);
	t[6].img = (*xpm)(cub->mlx, "./imgs/redsky.xpm", &t[6].a, &t[6].b);
	t[7].img = (*xpm)(cub->mlx, "./imgs/tabdeath.xpm", &t[7].a, &t[7].b);
	t[8].img = (*xpm)(cub->mlx, "./imgs/mapbg.xpm", &t[8].a, &t[8].b);
	t[9].img = (*xpm)(cub->mlx, "./imgs/redsky2.xpm", &t[9].a, &t[9].b);
	while (++i < 10)
		if (!t[i].img)
			return (0);
	cub->imap = mlx_new_image(cub->mlx, 9 * 16, 9 * 16);
	cub->iray = mlx_new_image(cub->mlx, HRES - 1, VRES -1);
	if (!cub->imap || !cub->iray)
		return (0);
	return (1);
}

int	create_imgs(t_cub *cub)
{
	t_text imgs[10];

	cub->text = &imgs;
	if (!imgs(cub, &imgs, mlx_xpm_file_to_image))
		return (0);
	if (!addr(cub, &imgs, mlx_get_data_addr))
		return (0);
	return (1);
}

void	destroy_imgs(t_cub *cub, t_text *imgs)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (imgs[i].img)
			mlx_destroy_image(cub->mlx, imgs[i].img);
		i++;
	}
	if (cub->imap)
		mlx_destroy_image(cub->mlx, cub->imap);
	if (cub->iray)
		mlx_destroy_image(cub->mlx, cub->iray);
}
