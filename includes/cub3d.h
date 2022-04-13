/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:35:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/13 01:53:24 by anremiki         ###   ########.fr       */
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
# include "/usr/include/X11/X.h"
# include "../libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"
//# include "struct3d.h"
//# include "define.h"

# define PI 3.1415926535
# define NVALUE 0.017452925
# define RAD 0.017452925

enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR,
	GATHER
};

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

typedef struct s_text
{
	void	*texture;
	void	*addr;
	char	*name;
	int		bpp;
	int		size;
	int		end;
	int		a;
	int		b;
}				t_text;

typedef struct s_hud
{
	void	*hud;
	int		a;
	int		b;
}				t_hud;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_hud	*hud;
	float	anim;
	void	*imap;
	char	*addr;
	char	**map;
	char	**exp;
	char	**pixmap;
	int		n_imgs;
	int		color;
	int		bpp;
	int		bbpp;
	int		raysize;
	int		size_line;
	int		bsize_line;
	int		imgsize;
	int		next;
	int		endian;
	int		bendian;
	void	*iplayer;
	void	*texture;
	char	*textaddr;
	char	**rtext;
	int		last_ray;
	int		i;
	int		j;
	int		bg_r;
	int		bg_g;
	int		bg_b;
	int		hres;
	int		vres;
	int		mx;
	int		my;
	int		ex;
	int		ey;
	int		fov;
	float	dra;
	float	px;
	float	pdx;
	float	py;
	float	pdy;
	float	validx;
	float	validy;
	double	pa;
	double	pz;
	int		brightness;
	int		released;
	int		last_pressed;
	int		press_start;
	double	sprint;
	int		end;
	int		paintings;
	float	lx;
	float	la;
	float	ly;
	float	lz;
	float	pi2;
	float	dpi;
	float	pi3;
	int		magic;
	t_text	*text;
	void	*b1;
	void	*b2;
	void	*b3;
}			t_mlx;

/*	Parsing data	*/

/*int		init_data(char **av, t_cub *cub);
int		gather_data(char *av, t_parse *data, int fd, t_cub *cub);
int		split_data(t_parse *data, t_cub *cub);*/
int		check_valid(char c, char *sep);
int		check_comma(char *line);
int		check_rgb(char *line);
int		check_path(char *line, int arg);
int		parse_line(char *line, int arg);
char	*ft_strndup(char *str, int limit);
char	*skip_line(char *line);
char	**parse_data(char **av);
char	**parse_map(char **map);

/* Engine modification	*/

void	printmap(char **map);
void	modify_map(char **map, char **exp, int mult);
char	**expand(char **map, int x, int y, int mult);

#endif
