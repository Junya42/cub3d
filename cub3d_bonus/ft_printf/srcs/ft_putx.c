/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:42:36 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/03 16:25:23 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_xsize(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_putx(unsigned int n, char x, int fd)
{
	if (n > 15)
		ft_putx(n / 16, x, fd);
	if ((n % 16) < 10)
		ft_putchar((n % 16) + '0', fd);
	else
		ft_putchar((n % 16) + x - 33, fd);
}

int	ft_returnputx(unsigned int n, char x, int fd)
{
	ft_putx(n, x, fd);
	return (ft_get_xsize(n));
}
