/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 00:38:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/03 16:24:29 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)", fd));
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}
