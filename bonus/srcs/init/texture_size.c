/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:04:58 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/31 15:48:58 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	walls_txt_size(t_text *t)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (t[i].a != t[i].b)
		{
			printf("TEXTURE IS NOT A SQUARE %dx%d\n", t[i].a, t[i].b);
			return (0);
		}
		if (t[i].a != 64 && t[i].a != 128)
		{
			printf("TXT SIZE ERROR SHOULD (64x64 OR 128x128) HAVING %dx%d\n",
				t[i].a, t[i].b);
			return (0);
		}
		if (t[i].b != 64 && t[i].b != 128)
		{
			printf("TXT SIZE ERROR SHOULD (64x64 OR 128x128) HAVING %dx%d\n",
				t[i].a, t[i].b);
			return (0);
		}
		i++;
	}
	return (1);
}