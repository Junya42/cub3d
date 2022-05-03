/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:25:29 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/03 09:14:14 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_matrix(char ***matrix, int	a, int b, int c)
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

char	**allocate_sub_matrix(char ***matrix, int a, int b, int c)
{
	char	**tmp;

	tmp = NULL;
	tmp = (char **)malloc(sizeof(char *) * b);
	if (!tmp)
	{
		free_matrix(matrix, a, b, c);
		return (NULL);
	}
	return (tmp);
}

char	*allocate_last_matrix(char ***matrix, int a, int b, int c)
{
	char	*tmp;

	tmp = NULL;
	tmp = (char *)malloc(sizeof(char *) * c);
	if (!tmp)
	{
		free_matrix(matrix, a, b, c);
		return (NULL);
	}
	return (tmp);
}

char	***allocate_matrix(int a, int b, int c)
{
	char	***matrix;
	int		i;
	int		j;

	matrix = (char ***)malloc(sizeof(char **) * a);
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (i < a)
	{
		matrix[i] = allocate_sub_matrix(matrix, a, b, c);
		if (!matrix[i])
			return (NULL);
		j = 0;
		while (matrix[i][j])
		{
			matrix[i][j] = allocate_last_matrix(matrix, a, b, c);
			if (!matrix[i][j])
				return (NULL);
			j++;
		}
		i++;
	}
	return (matrix);
}
