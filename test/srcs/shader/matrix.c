/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:25:29 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/03 14:38:18 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_matrix(char ***matrix, int b, int c)
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

char	**allocate_sub_matrix(char ***matrix, int b, int c)
{
	char	**tmp;

	tmp = NULL;
	tmp = (char **)malloc(sizeof(char *) * b);
	if (!tmp)
	{
		free_matrix(matrix, b, c);
		return (NULL);
	}
//	tmp = ft_memset(tmp, 49, b);
	return (tmp);
}

char	*allocate_last_matrix(char ***matrix, int b, int c)
{
	char	*tmp;

	tmp = NULL;
	tmp = (char *)malloc(sizeof(char) * c);
	if (!tmp)
	{
		free_matrix(matrix, b, c);
		return (NULL);
	}
//	tmp = ft_memset(tmp, 49, c);
	return (tmp);
}

char	***allocate_matrix(int a, int b, int c)
{
	char	***matrix;
	int		i;
	int		j;

	matrix = NULL;
	matrix = (char ***)malloc(sizeof(char **) * a);
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
		while (matrix[i][j])
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
	printf("matrix allocation success\n");
	return (matrix);
}
