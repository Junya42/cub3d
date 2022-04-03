/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:40:50 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/03 16:24:51 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	u_size(unsigned int n, int size)
{
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

void	ft_putunbr(unsigned int n, int fd)
{
	if (n > 9)
		ft_putunbr(n / 10, fd);
	ft_putchar((n % 10) + '0', fd);
}

int	ft_putunbrsize(unsigned int n, int fd)
{
	ft_putunbr(n, fd);
	return (u_size(n, 0));
}
