/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 01:24:23 by anremiki          #+#    #+#             */
/*   Updated: 2022/03/26 15:35:16 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long int	res;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -sign;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (res * sign > INT_MAX)
			return (-1);
		if (res * sign < INT_MIN)
			return (0);
		res = res * 10 + *(nptr++) - 48;
	}
	return (res * sign);
}
