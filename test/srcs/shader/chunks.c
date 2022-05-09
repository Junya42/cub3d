/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 00:47:38 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/09 17:47:49 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	assign_light_values(t_cub *cub, t_light *light, t_sp *sp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->nb_sprites)
	{
		if (sp[i].s_type == LIGHT)
		{
			light[j].x = sp[i].x;
			light[j].y = sp[i].y;
			light[j].angle = PI;
			light[j].range = 0;
			light[j].id = j + 1;
			light[j].chunk = 64;
			light[j].cursor = 0;
			light[j].color = sp[i].hue;
			j++;
		}
		i++;
	}
}

t_light	*create_lights(t_cub *cub, t_sp *sp)
{
	t_light	*light;
	t_ray	ray;
	int		i;

	i = -1;
	light = (t_light *)malloc(sizeof(t_light) * cub->lights);
	if (!light)
		return (NULL);
	assign_light_values(cub, light, sp);
	cub->chunk = allocate_matrix(cub->ey, cub->ex, cub->lights);
	while (++i < cub->lights)
		chunk(cub, &light[i], &ray);
	return (light);
}
