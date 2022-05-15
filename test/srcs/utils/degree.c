/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:26:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/15 12:29:04 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float degree_convert(float angle)
{
	return (angle * 180 / PI);
}

int	quadrant_direction(float angle)
{
	int	degree;

	degree = degree_convert(angle);
	if (degree > 315 || degree < 45)
		return (1);
	if (degree >= 45 && degree < 135)
		return (2);
	if (degree >= 135 && degree < 225)
		return (3);
	if (degree >= 225 && degree <= 315)
		return (4);
	return (0);
}
