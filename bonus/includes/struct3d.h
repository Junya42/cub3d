/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:05:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/24 19:03:03 by anremiki         ###   ########.fr       */
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
	F,
	OW,
	F1,
	F2,
	R1,
	R2
};

enum	e_sprite_type
{
	PC,
	STATUE,
	BIG_STATUE,
	GRASS,
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

enum	e_lightcol
{
	LSHADE,
	LRED,
	LBLUE,
	LPURPLE,
	LGREEN,
	LYELLOW,
	LCYAN
};

typedef struct s_parse
{
	int				side;
	int				i;
	int				total;
	int				fd;
	int				*width;
	int				height;
	char			*str;
	char			*buffer;
	char			**mcontent;
	int				check_ne;
	int				check_so;
	int				check_we;
	int				check_ea;
	int				check_o;
	int				check_r1;
	int				check_r2;
	int				check_f1;
	int				check_f2;
	int				check_c;
	int				check_f;
	char			*npath;
	char			*spath;
	char			*wpath;
	char			*epath;
	char			*o_path;
	char			*r1_path;
	char			*r2_path;
	char			*f1_path;
	char			*f2_path;
	unsigned int	colorc;
	unsigned int	colorf;
	char			**all_map;
	char			**map;
	char			**roof;
	char			**floor;
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

typedef struct s_exp
{
	char	**exp;
	int		xcurs;
	int		ycurs;
	int		ex;
	int		ey;
}			t_exp;

typedef	struct s_matrix
{
	int	***matrix;
	int	i;
	int	j;
	int	k;
	int	a;
	int	b;
	int	c;
}			t_matrix;

typedef struct s_csp
{
	int				type;
	int				z;
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

typedef struct s_cast
{
	float			heightfix;
	float			fix;
	unsigned int	color;
	float			distx;
	float			disty;
	float			dceilx;
	float			dceily;
	float			ceilx;
	float			ceily;
	float			ra_sky;
	int				ceilcheck;
	int				i;
	int				limiter;
	int				flag;
}				t_cast;

typedef struct s_ray
{
	float			l1;
	float			l2;
	float			offset;
	float			raycast;
	float			diff;
	float			contan;
	float			ntan;
	int				r;
	float			ray;
	float			ra;
	float			dra;
	double			rx;
	double			ry;
	double			saverx;
	double			savery;
	double			npx;
	double			npy;
	float			nr;
	float			bigpx;
	float			bignpx;
	float			curr_px;
	float			next_px;
	float			floor_x;
	float			floor_y;
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
	float			out;
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
	float	x;
	float	y;
	int		chunk;
	int		id;
	int		range;
	int		color;
	int		cursor;
}				t_light;

typedef struct s_lightmath
{
	float	dist;
	float	dx;
	float	dy;
	float	shade;
	int		i;
	int		count;
}				t_lightmath;

typedef struct s_cub
{
	Mix_Chunk		*light_aura;
	Mix_Chunk		*door_opening;
	Mix_Chunk		*teleportation;
	Mix_Chunk		*foot_steps[4];
	Mix_Music		*opening_theme;
	int				id;
	int				closed;
	int				debug;
	int				sp_error;
	int				exit_code;
	int				mixing;
	int				foot;
	int				lights;
	void			*mlx;
	void			*win;
	void			*erase;
	void			*imap;
	void			*ihud;
	void			*iray;
	char			*no;
	char			*ea;
	char			*so;
	char			*we;
	char			*mapaddr;
	char			*rayaddr;
	int				m_bpp;
	int				m_size;
	int				m_end;
	int				r_bpp;
	int				r_size;
	int				r_end;
	int				hue;
	unsigned int	color;
	unsigned int	scolor;
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
	float			blocked;
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
	int				sp_dist;
	int				pause;
	float			sp_angle;
	long long		curr_time;
	long long		time_move;
	float			lastx;
	float			lasty;
	int				*map_len;
	int				map_height;
	char			**data;
	char			**roof;
	char			**floor;
	char			**map;
	char			**exp;
	char			**expl;
	char			**expr;
	int				***chunk;
	float			scroll;
	int				brightness;
	float			door;
	int				doorcheck;
	int				degree;
	int				vglass;
	int				hglass;
	int				glass;
	int				top;
	int				bot;
	int				right;
	int				left;
	int				out;
	t_ray			*ray;
	t_player		*player;
	t_text			*text;
	t_sp			*sp;
	t_light			*light;
}				t_cub;

#endif
