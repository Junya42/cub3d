/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:54:20 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 14:55:07 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	free_array(char **ptr)
{
	int	i;

	i = -1;
	if (ptr)
	{
		while (ptr[++i])
		{
			if (ptr[i])
			{
				free(ptr[i]);
				ptr[i] = NULL;
			}
		}
		free(ptr);
		ptr = NULL;
	}
}
