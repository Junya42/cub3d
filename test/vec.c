/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:44:28 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/22 23:20:15 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

int main()
{
	float	angle = 0.78539816339;
	float	sx = 128;
	float	sy = 192;
	float	px = 384;
	float	py = 384 + 32;
	float	vsx = sx - px;
	float	vsy = sy - py;
	float	vx = cos(angle);
	float	vy = sin(angle);
	float	inverse = atan2(vy, vx);
	float	vecangle = acos((vsx * vx + vsy * vy) / (sqrt(vsx * vsx + vx * vx) * sqrt(vsy * vsy + vy * vy)));
	float	diff = (angle * 180 / 3.14) - (vecangle * 180 / 3.14);

	printf("angle %f\n", angle);
	printf("Vecteur player->sprite->x %f\n", vsx);
	printf("Vecteur player->sprite->y %f\n", vsy);
	printf("Vecteur angle.x %f\n", vx);
	printf("Vecteur angle.y %f\n", vy);
	printf("angle from vecteur angle %f\n", inverse);
	printf("Angle du Vecteur player->sprite %f\n", vecangle);
	printf("diff angle player et angle vecteur player->sprite en radian %f\n", angle - vecangle);
	printf("diff en degree %f\n", diff);
}
