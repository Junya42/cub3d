/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:46:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/11 01:38:47 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	mysqrt(float n)
{
	union
	{
		int		i;
		float	x;
	}	u;
	u.x = n;
	u.i = (1<<29) + (u.i >> 1) - (1 << 22);
	u.x = u.x + n / u.x;
	u.x = 0.25f * u.x + n / u.x;
	return (u.x);
}

float	dist(float ax, float ay, float bx, float by)
{
	return (mysqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float	fix_fisheye(float pa, float ra, float ray)
{
	float	fix;

	fix = pa - ra;
	if (fix < 0)
		fix += DPI;
	if ( fix > DPI)
		fix -= DPI;
	return (ray * (cos(fix)));
}

float	secure_radians(float angle, float delta)
{
	angle += delta;
	if (angle < 0)
		angle += DPI;
	if (angle > DPI)
		angle -= DPI;
	return (angle);
}

float	deg_to_rad(float angle, float degree)
{
	angle += (RAD * degree);
	if (angle < 0)
		angle += DPI;
	if (angle > DPI)
		angle -= DPI;
	return (angle);
}
