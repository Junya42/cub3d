/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:33:20 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/03 16:29:12 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	do_fmt(const char *format, va_list args, int fd)
{
	if (format[0] == 'c')
		return (ft_putchar(va_arg(args, int), fd));
	if (format[0] == 's')
		return (ft_putstr(va_arg(args, char *), fd));
	if (format[0] == 'p')
		return (ft_returnaddress(va_arg(args, unsigned long int), 'x', fd));
	if (format[0] == 'd')
		return (ft_putnbrsize(va_arg(args, int), fd));
	if (format[0] == 'i')
		return (ft_putnbrsize(va_arg(args, int), fd));
	if (format[0] == 'u')
		return (ft_putunbrsize(va_arg(args, unsigned int), fd));
	if (format[0] == 'x' || format[0] == 'X')
		return (ft_returnputx(va_arg(args, unsigned int), format[0], fd));
	if (format[0] == '%')
		return (ft_putchar('%', fd));
	return (ft_putchar('%', fd));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		fd;
	int		i;
	int		j;

	i = -1;
	j = 0;
	fd = 1;
	va_start(args, format);
	if (format[i] == '!' && fd++)
		i++;
	while (format[++i])
	{
		if (format[i] != '%')
			j += ft_putchar(format[i], fd);
		else
			if (format[i + 1])
				j += do_fmt(&format[++i], args, fd);
	}
	if (format[i - 1] == '%' && format[i - 2] != '%')
		j += ft_putchar('%', fd);
	va_end(args);
	return (j);
}
