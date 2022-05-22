/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/21 12:45:06 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	return (tmp);
}

int	init_matrix(t_matrix *m, int a, int b, int c)
{
	m->matrix = (int ***)malloc(sizeof(int **) * a);
	if (!m->matrix)
	{
		printf("Matrix Malloc failure\n");
		return (0);
	}
	m->i = 0;
	m->j = 0;
	m->a = a;
	m->b = b;
	m->c = c;
	return (1);
}

void	fill_matrix(t_matrix *m)
{
	m->i = 0;
	while (m->i < m->a)
	{
		m->j = 0;
		while (m->j < m->b)
		{
			m->k = 0;
			while (m->k < m->c)
			{
				m->matrix[m->i][m->j][m->k] = 0;
				m->k++;
			}
			m->j++;
		}
		m->i++;
	}
}

int	***allocate_matrix(int a, int b, int c)
{
	t_matrix	m;

	if (!init_matrix(&m, a, b, c))
		return (NULL);
	while (m.i < a)
	{
		m.matrix[m.i] = allocate_sub_matrix(m.matrix, b, c);
		if (!m.matrix[m.i])
			return (err_matrix("Sub Matrix malloc failure"));
		m.j = 0;
		while (m.j < b)
		{
			m.matrix[m.i][m.j] = allocate_last_matrix(m.matrix, b, c);
			if (!m.matrix[m.i][m.j])
				return (err_matrix("Last Matrix malloc failure"));
			m.j++;
		}
		m.i++;
	}
	fill_matrix(&m);
	return (m.matrix);
}
