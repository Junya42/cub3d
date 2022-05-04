/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:25:29 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/04 12:59:46 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_matrix(int ***matrix, int b, int c)
{
	int	i;
	int	j;

	printf("free matrix\n");
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

int	**allocate_sub_matrix(int ***matrix, int b, int c)
{
	int	**tmp;

	tmp = NULL;
	tmp = (int **)malloc(sizeof(int *) * b);
	if (!tmp)
	{
		free_matrix(matrix, b, c);
		return (NULL);
	}
//	tmp = ft_memset(tmp, 49, b);
	return (tmp);
}

int	*allocate_last_matrix(int ***matrix, int b, int c)
{
	int	*tmp;

	tmp = NULL;
	tmp = (int *)malloc(sizeof(int) * c);
	if (!tmp)
	{
		free_matrix(matrix, b, c);
		return (NULL);
	}
//	tmp = ft_memset(tmp, 49, c);
	return (tmp);
}

int	***allocate_matrix(int a, int b, int c)
{
	int	***matrix;
	int		i;
	int		j;

	matrix = (int ***)malloc(sizeof(int **) * a);
	if (!matrix)
	{
		printf("Matrix malloc failure\n");
		return (NULL);
	}
	//matrix = ft_memset(matrix, 0, a);
	i = 0;
	j = 0;
	while (i < a)
	{
		matrix[i] = allocate_sub_matrix(matrix, b, c);
		if (!matrix[i])
		{
			printf("Sub Matrix malloc failure\n");
			return (NULL);
		}
		j = 0;
		while (j < b)
		{
			matrix[i][j] = allocate_last_matrix(matrix, b, c);
			if (!matrix[i][j])
			{
				printf("Last Matrix malloc failure\n");
				return (NULL);
			}
			j++;
		}
		i++;
	}
	for (i = 0; i < a; i++)
	{
		for (j = 0; j < b; j++)
		{
			for (int k = 0; k < c; k++)
				matrix[i][j][k] = 0;
		}
	}
	printf("matrix allocation success\n");
	return (matrix);
}
