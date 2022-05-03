/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:05:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/03 13:28:04 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT3D_H
# define STRUCT3D_H

# include "./define.h"

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

enum	e_sprite_type
{
	PC,
};

enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR,
	gnl_loop
};

enum	e_color
{
	SHADE,
	RED,
	GREEN,
	BLUE,
	CYAN,
	PURPLE,
	YELLOW
};

typedef struct s_parse
{
	int				i;
	int				total;
	int				fd;
	char			*buffer;
	char			**mcontent;
	int				check_ne;
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

typedef struct s_player
{
	float	x;
	float	y;
	double	z;
	float	safex;
	float	safey;
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

typedef struct s_csp
{
	int				type;
	int				moveable;
	int				size;
	int				dbpp;
	float			index;
	float			dist;
	float			sx;
	float			sy;
	float			a;
	float			b;
	float			CS;
	float			SN;
	int				bpp;
	int				sizeline;
	int				endian;
	int				ae;
	int				be;
	void			*img;
	void			*addr;
	char			*tmp;
	unsigned int	color;
	float			j;
	float			x;
	float			scale;
	float			ncolor;
	float			cx;
	float			cy;
}			t_csp;

typedef struct s_anim
{
	void	*img;
	char	*addr;
	int		a;
	int		b;
	int		bpp;
	int		size;
	int		end;  
}			t_anim;

typedef struct s_sp
{
	char	*anim_paths[8];
	int		animated;
	char	type;
	int		s_type;
	int		hue;
	void	*img;
	char	*addr;
	float	x;
	float	y;
	int		z;
	int		a;
	int		b;
	int		bpp;
	int		dbpp;
	int		sizeline;
	int		size;
	int		end;
	int		index;
	t_csp	csp;
	t_anim	anim[NB_FRAME];
}			t_sp;

typedef struct s_ray
{
	float			l1;
	float			l2;
	float			offset;
	float			raycast;
	float			contan;
	float			ntan;
	int				r;
	float			ray;
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
	double			camx;
	double			raydirx;
	double			raydiry;
	double			wallx;
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

typedef struct s_light
{
	float	angle;
	int		x;
	int		y;
	int		chunk;
	int		id;
	int		range;
	int		color;
	int		cursor;
}				t_light;

typedef struct s_cub
{
	int				lights;
	void			*mlx;
	void			*win;
	void			*imap;
	void			*ihud;
	void			*iray;
	char			*no;
	char			*ea;
	char			*so;
	char			*we;
	char			*mapaddr;
	char			*rayaddr;
	//int				nsprite;
	int				m_bpp;
	int				m_size;
	int				m_end;
	int				r_bpp;
	int				r_size;
	int				r_end;
	unsigned int	color;
	unsigned int	fcolor;
	unsigned int	ccolor;
	float			n_rad;
	float			s_rad;
	float			x;
	float			y;
	float			a;
	float			sin;
	float			cos;
	float			z;
	double			h;
	double			xplane;
	double			yplane;
	int				jump;
	int				dir;
	int				mx;
	int				my;
	int				mp;
	int				ex;
	int				ey;
	int				end;
	int				flot;
	int				search_i;
	int				search_j;
	int				nb_sprites;
	float			sz;
	int				zbuf[NRAY];
	int				update;
	char			**data;
	char			**map;
	char			**exp;
	char			***chunk;
	//t_build			*build;
	float			scroll;
	int				brightness;
	t_ray			*ray;
	t_player		*player;
	t_text			*text;
	t_sp			*sp;
	t_light			*light;
}				t_cub;

/*typedef struct s_parse
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
  */
#endif