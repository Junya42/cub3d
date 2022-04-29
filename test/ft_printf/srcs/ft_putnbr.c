/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:23:27 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/03 16:29:41 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	d_size(int n, int size)
{
	if (n <= 0)
		size++;
	else
		n = -n;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

void	ft_putnbr(int n, int fd)
{
	if (n >= 0)
		n = -n;
	else
		ft_putchar('-', fd);
	if (n < -9)
		ft_putnbr(-(n / 10), fd);
	ft_putchar(-(n % 10) + '0', fd);
}

int	ft_putnbrsize(int n, int fd)
{
	ft_putnbr(n, fd);
	return (d_size(n, 0));
}
