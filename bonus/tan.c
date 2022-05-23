/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tan.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 06:11:49 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/26 06:55:35 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

int main()
{
	double pi = 2 * 3.14159265359;
	double angle = 3.14159265359;
	double dirx = -1;
	double diry = 0;
	double planex = 0;
	double planey = 0.66;
	double rot = 0.07;

	double oldirx = dirx;
	dirx = dirx * cos(-rot) - diry * sin(-rot);
	diry = oldirx * sin(-rot) + diry * cos(-rot);
	double oldplanex = planex;
	planex = planex * cos(-rot) - planey * sin(-rot);
	planey = oldplanex * sin(-rot) + planey * cos(-rot);
	angle += -rot;
	if (angle < 0)
		angle += pi;
	if (angle > pi)
		angle -= pi;
	printf("angle : %f\n", angle);
	printf("cos angle : %f\n", cos(angle));
	printf("sin angle : %f\n", sin(angle));
	printf("dirX : %f\n", dirx);
	printf("dirY : %f\n", diry);
	printf("planeX : %f\n", planex);
	printf("planeY : %f\n", planey);
	printf("distance player -> projection plane =\n- Width / 2 / tan(deg_to_radian(FOV / 2)) =\n- 512 / tan(0.523599) =\n- %f\n- %f\n",
			(512.0 / tan(0.523599)), (256.0 / tan(0.523599)));
}
