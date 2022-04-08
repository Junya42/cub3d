/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 06:05:23 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/07 06:08:49 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned int	ft_abs(int value)
{
	const int		mask;
	unsigned int	abs;

	mask = value >> sizeof(int) * CHAR_BIT - 1;
	abs = (value + mask) ^ mask;
	return (abs);
}
