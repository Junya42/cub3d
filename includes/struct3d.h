/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:05:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/07 02:00:38 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT3D_H
# define STRUCT3D_H

# define PI 3.1415926535
# define RAD 0.0174532925

typedef struct s_player
{
	float	x;
	float	y;
	double	z;
	float	lstraf;
	float	rstraf;
	float	dx;
	float	dy;
	float	sens;
	double	angle;
	int		released;
	int		last_pressed;
	int		input_fix;
	double	ms;
	double	crouch;
}				t_player;

typedef struct s_ray
{
	float	ra;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	hray;
	float	hx;
	float	hy;
	float	vray;
	float	vx;
	float	vy;
	int		mx;
	int		my;
	int		limit;
	int		fov;
	int		nray;
}				t_ray;

typedef struct s_build
{
	int		mx;
	int		my;
	float	px;
	float	py;
	float	pa;
	char	player;
}

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	void		*imap;
	void		*ihud;
	void		*iray;
	void		*no;
	void		*ea;
	void		*so;
	void		*we;
	char		*mapaddr;
	char		*rayaddr;
	int			bpp;
	int			size_line;
	int			endian;
	int			color;
	int			fcolor;
	int			ccolor;
	float		n_rad;
	float		s_rad;
	int			mx;
	int			my;
	int			mp;
	int			wx;
	int			wy;
	int			end;
	char		**data;
	char		**map;
	t_build		*build;
	t_ray		*ray;
	t_player	*player;
}				t_cub;

typedef struct s_parse
{
	char	**map;
	char	**data;
	char	*tmpdata;
	char	*total;
	char	*line;
	int		fd;
	int		arg;
	int		checker;
	int		map_start;
	int		x;
}				t_parse;

#endif
