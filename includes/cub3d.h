/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:35:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/03 00:19:17 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../libft/srcs/libft.h"

enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR
};

/* PARSING */
int	exit_parsing(char *str);
int	parsing(char **av);
/* PARSING */

#endif