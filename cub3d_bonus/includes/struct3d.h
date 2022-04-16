/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:05:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/16 18:47:54 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT3D_H
# define STRUCT3D_H

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
	float			offset;
	float			raycast;
	float			contan;
	float			ntan;
	float			ra;
	float			dra;
	float			rx;
	float			ry;
	float			npx;
	float			npy;
	float			nr;
	float			curr_px;
	float			next_px;
	float			off_px;
	float			xo;
	float			yo;
	float			hray;
	float			hx;
	float			hy;
	float			vray;
	float			vx;
	float			vy;
	float			shadow;
	float			top;
	float			bot;
	float			left;
	float			right;
	float			offj;
	unsigned int	color;
	int				i;
	int				j;
	int				mx;
	int				my;
	int				hdir;
	int				vdir;
	int				limit;
	int				fov;
	int				nray;
}				t_ray;

typedef struct s_build
{
	int		mx;
	int		my;
	float	px;
	float	py;
	float	pa;
	char	player;
}				t_build;

typedef struct s_text
{
	void	*img;
	void	*addr;
	int		bpp;
	int		size;
	int		end;
	int		a;
	int		b;
}			t_text;

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
	float		x;
	float		y;
	float		a;
	int			mx;
	int			my;
	int			mp;
	int			ex;
	int			ey;
	int			wx;
	int			wy;
	int			end;
	char		**data;
	char		**map;
	char		**exp;
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
