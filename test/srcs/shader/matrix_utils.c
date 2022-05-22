/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:36 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/21 12:43:39 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_matrix(int ***matrix, int b, int c)
{
	int	i;
	int	j;

	if (matrix)
	{
		i = 0;
		while (i < b)
		{
			j = 0;
			if (matrix[i])
			{
				while (j < c)
				{
					if (matrix[i][j])
						free(matrix[i][j]);
					j++;
				}
				free(matrix[i]);
			}
			i++;
		}
		free(matrix);
	}
}

int	***err_matrix(char *error)
{
	printf("%s\n", error);
	return (NULL);
}
