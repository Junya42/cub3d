/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:26:46 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/16 02:05:09 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	deg_to_rad(float angle, float degree)
{
	angle += (0.0174533 * degree);
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

float	fixfisheye(float pa, float ra, float distT)
{
	float	fix;

	if (!distT)
		return (0);
	fix = pa - ra;
	if (fix < 0)
		fix += 2 * PI;
	if (fix > 2 * PI)
		fix -= 2 * PI;
	return (distT * cos(fix));
}
