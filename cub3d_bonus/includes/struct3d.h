/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:05:01 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/23 07:37:38 by anremiki         ###   ########.fr       */
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

typedef struct s_ray
{
	float			offset;
	float			raycast;
	float			contan;
	float			ntan;
	float			r;
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
	float			z;
	double			h;
	int				jump;
	int				dir;
	int				mx;
	int				my;
	int				mp;
	int				ex;
	int				ey;
	int				end;
	char			**data;
	char			**map;
	char			**exp;
	//t_build			*build;
	float			scroll;
	t_ray			*ray;
	t_player		*player;
	t_text			*text;
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
