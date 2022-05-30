/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:54:51 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/30 23:14:59 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	bonus_side(char **mcontent)
{
	if (ft_strncmp(mcontent[0], "OW", 2) == 0)
		return (OW);
	if (ft_strncmp(mcontent[0], "F1", 2) == 0)
		return (F1);
	if (ft_strncmp(mcontent[0], "F2", 2) == 0)
		return (F2);
	if (ft_strncmp(mcontent[0], "R1", 2) == 0)
		return (R1);
	if (ft_strncmp(mcontent[0], "R2", 2) == 0)
		return (R2);
	if (ft_strncmp(mcontent[0], "F", 1) == 0)
		return (F);
	if (ft_strncmp(mcontent[0], "C", 1) == 0)
		return (C);
	return (NOTHING);
}

static inline int	bonus_direction_bis(char *side, t_parse *p)
{
	if (ft_strncmp(side, "R1", 2) == 0 && p->check_r1 == 0)
	{
		p->check_r1 = 1;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(side, "R2", 2) == 0 && p->check_r2 == 0)
	{
		p->check_r2 = 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	bonus_direction(char *side, t_parse *p)
{
	if (ft_strncmp(side, "OW", 2) == 0 && p->check_o == 0)
	{
		p->check_o = 1;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(side, "F1", 2) == 0 && p->check_f1 == 0)
	{
		p->check_f1 = 1;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(side, "F2", 2) == 0 && p->check_f2 == 0)
	{
		p->check_f2 = 1;
		return (EXIT_SUCCESS);
	}
	return (bonus_direction_bis(side, p));
}
