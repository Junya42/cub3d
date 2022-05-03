/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:30:53 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/28 05:45:56 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	addr(t_cub *cub, t_text *t, char *(*add)(void *, int *, int *, int *))
{
	int	i;

	i = -1;
	cub->mapaddr = (*add)(cub->imap, &cub->m_bpp, &cub->m_size, &cub->m_end);
	cub->rayaddr = (*add)(cub->iray, &cub->r_bpp, &cub->r_size, &cub->r_end);
	if (!cub->mapaddr || !cub->rayaddr)
		return (0);
	t[0].addr = cub->rayaddr;
	t[1].addr = (*add)(t[1].img, &t[1].bpp, &t[1].size, &t[1].end);
	t[2].addr = (*add)(t[2].img, &t[2].bpp, &t[2].size, &t[2].end);
	t[3].addr = (*add)(t[3].img, &t[3].bpp, &t[3].size, &t[3].end);
	t[4].addr = (*add)(t[4].img, &t[4].bpp, &t[4].size, &t[4].end);
	t[5].addr = (*add)(t[5].img, &t[5].bpp, &t[5].size, &t[5].end);
	t[6].addr = (*add)(t[6].img, &t[6].bpp, &t[6].size, &t[6].end);
	printf("bpp = %d\n", t[6].bpp);
	t[7].addr = (*add)(t[7].img, &t[7].bpp, &t[7].size, &t[7].end);
	t[8].addr = (*add)(t[8].img, &t[8].bpp, &t[8].size, &t[8].end);
	t[9].addr = (*add)(t[9].img, &t[9].bpp, &t[9].size, &t[9].end);
	t[10].addr = (*add)(t[10].img, &t[10].bpp, &t[10].size, &t[10].end);
	while (++i < 11)
		if (!t[i].addr)
			return (0);
	return (1);
}

int	imgs(t_cub *cub, t_text *t, void *(*xpm)(void *, char *, int *, int *))
{
	int	i;

	i = -1;
	t[0].img = mlx_new_image(cub->mlx, HRES, VRES);
	//t[0].img = (*xpm)(cub->mlx, "./imgs/torch2.xpm", &t[0].a, &t[0].b);
	t[1].img = (*xpm)(cub->mlx, "./imgs/bookshelf.xpm", &t[1].a, &t[1].b);
	t[2].img = (*xpm)(cub->mlx, "./imgs/birch_planks.xpm", &t[2].a, &t[2].b);
	t[3].img = (*xpm)(cub->mlx, "./imgs/blackstone.xpm", &t[3].a, &t[3].b);
	t[4].img = (*xpm)(cub->mlx, "./imgs/bricks.xpm", &t[4].a, &t[4].b);
	t[5].img = (*xpm)(cub->mlx, "./imgs/pblackstone.xpm", &t[5].a, &t[5].b);
	t[6].img = (*xpm)(cub->mlx, "./imgs/doomfloor.xpm", &t[6].a, &t[6].b);
	t[7].img = (*xpm)(cub->mlx, "./imgs/null.xpm", &t[7].a, &t[7].b);
	printf("7 a : %d\n", t[7].a);
	printf("7 b : %d\n", t[7].b);
	t[8].img = (*xpm)(cub->mlx, "./imgs/tabdeath.xpm", &t[8].a, &t[8].b);
	t[9].img = (*xpm)(cub->mlx, "./imgs/torch2.xpm", &t[9].a, &t[9].b);
	t[10].img = (*xpm)(cub->mlx, "./imgs/redskyfix.xpm", &t[10].a, &t[10].b);
	while (++i < 11)
		if (!t[i].img)
			return (0);
	cub->imap = mlx_new_image(cub->mlx, 9 * 16, 9 * 16);
	cub->iray = mlx_new_image(cub->mlx, HRES, VRES);
	if (!cub->imap || !cub->iray)
		return (0);
	return (1);
}

int	create_imgs(t_cub *cub)
{
	//t_text images[11];
	t_text	*images;

	images = (t_text *)malloc(sizeof(t_text) * 11);

	if (!imgs(cub, images, mlx_xpm_file_to_image))
		return (0);
	if (!addr(cub, images, mlx_get_data_addr))
		return (0);
	cub->text = images;
	return (1);
}

void	destroy_imgs(t_cub *cub, t_text *imgs)
{
	int	i;

	i = 0;
	while (i < 11)
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