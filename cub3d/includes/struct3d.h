/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:05:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/17 01:17:50 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT3D_H
# define STRUCT3D_H

enum	e_side
{
	NOTHING,
	N,
	S,
	W,
	E,
	C,
	F
};

enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR,
	gnl_loop
};

typedef struct s_parse
{
	int				total;
	int				fd;
	char			*buffer;
	char			**mcontent;
	int				check_no;
	int				check_so;
	int				check_we;
	int				check_ea;
	int				check_c;
	int				check_f;
	char			*npath;
	char			*spath;
	char			*wpath;
	char			*epath;
	unsigned int	colorc;
	unsigned int	colorf;
	char			**map;
}				t_parse;

typedef struct s_txt
{
	char			*path;
	int				a;
	int				b;
	void			*img;
	int				sizeline;
	int				bpp;
	int				end;
	char			*addr;
}				t_txt;

typedef struct s_ray
{
	float			sin;
	float			cos;
	unsigned int	colorc;
	unsigned int	colorf;
	int				x;
	int				y;
	char			*addr;
	int				bpp;
	int				sizeline;
	int				end;
	unsigned int	tcolor;
	void			*img;
	t_txt			txt[5];
	char			**paths;
	float			offset;
	float			dby;
	float			dy;
	float			north;
	float			south;
	float			east;
	float			west;
	float			strafel;
	float			strafer;
	int				hdir;
	int				vdir;
	float			vray;
	float			hray;
	void			*erase;
	char			**map;
	int				width;
	int				height;
	void			*mlx;
	void			*win;
	float			px;
	float			py;
	float			pdx;
	float			pdy;
	float			pa;
	int				move;
	int				color;
	float			ray;
	int				mx;
	int				my;
	int				mp;
	int				i;
	int				dof;
	float			rx;
	float			ry;
	float			ra;
	float			xo;
	float			yo;
	float			atan;
	float			ntan;
	float			hx;
	float			hy;
	float			vx;
	float			vy;
	float			distt;
	int				wallh;
	int				quit;
}				t_ray;

#endif
