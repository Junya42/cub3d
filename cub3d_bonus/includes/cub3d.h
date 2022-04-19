/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:35:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/19 15:59:46 by anremiki         ###   ########.fr       */
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
# include "struct3d.h"
# include "define.h"

//# define PI 3.1415926535
# define NVALUE 0.017452925
# define RAD 0.017452925
/*
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
*/
/*	Parsing data	*/

/*int		init_data(char **av, t_cub *cub);
int		gather_data(char *av, t_parse *data, int fd, t_cub *cub);
int		split_data(t_parse *data, t_cub *cub);
int		check_valid(char c, char *sep);
int		check_comma(char *line);
int		check_rgb(char *line);
int		check_path(char *line, int arg);
int		parse_line(char *line, int arg);
char	*ft_strndup(char *str, int limit);
char	*skip_line(char *line);
char	**parse_data(char **av);
char	**parse_map(char **map); */

/*		kekw	*/

void			free_data(t_parse *parse);
int				free_and_return(t_parse *p, int flag, int exitcode);
int				is_num(char *str);
int				get_fd_size(char *filename);
int				is_charset(char c, char *set);

/*		kekw2	*/

void			free_data(t_parse *parse);
int				free_and_return(t_parse *p, int flag, int exitcode);
int				is_num(char *str);
int				get_fd_size(char *filename);
int				is_charset(char c, char *set);void			init_variable(t_parse *p);
int				parsing(char **av, t_parse *parse);
int				parse_data(t_parse *parse);
int				parse_map(t_parse *parse, char *fd_path);
int				check_direction(char *side, t_parse *p);
int				check_texture_path(char *path);
int				check_floor_ceilings(char *side, t_parse *p);
int				check_rgb(char *code, int i);
int				check_map_content(char **mcontent, t_parse *p);
int				check_char(char **map, char *set);
int				closed_y(char **map, int x, int y);
int				closed_x(char **map, int x, int y);
int				out_of_bound(char **map, int reach_y, int reach_x);
int				check_closed_wall(char **map, int x, int y);
int				check_wall(char **map);
void			gather_data(char **mcontent, t_parse *p, int flag);
int				try_open_cub_file(char *filename, t_parse *parse);
int				exit_parsing(char *str);

/* -----------Engine mod-------		*/

void			printmap(char **map);
int				check_valid(char c, char *valid);
void			modify_map(char **map, char **exp, int mult);
char			**expand(char **map, int x, int y, int mult);
void			transform(char **map, int x, int y, char c);

/*	----------textures----------	*/

int				create_imgs(t_cub *cub);
void			destroy_imgs(t_cub *cub, t_text *imgs);

/*	----------init--------------	*/

void			init_cub(t_cub *cub);
//select
int				create_window(t_cub *cub);

/*	----------utils--------------	*/
/*	MATHS	*/
float			mysqrt(float n);
float			dist(float ax, float ay, float bx, float by);
float			fix_fisheye(float pa, float ra, float ray);
float			secure_radians(float angle, float delta);
float			deg_to_rad(float angle, float degree);
/*	MAP	*/
int				adjacent(t_cub *cub, int x, int y, char c);
void			change_map(t_cub *cub);
int				wipe_data(t_cub *cub);

/*	----------Pixels-------------	*/

void			pxl_to_img(t_cub *cub, float x, float y, int flag);
void			pxl_to_ray(t_cub *cub, float x, float y, unsigned int color);
unsigned int	pxl_from_img(t_cub *cub, int x, int y, int i);
unsigned int	rgb_to_hex(unsigned int r, unsigned int g, unsigned int b);
int				shade(int color, float shader);

/*	----------minimap-------------	*/

void			draw_player(t_cub *cub, float x, float y);
void			draw_posmap(t_cub *cub, char **map, int x, int y);

/*	----------raycast-------------	*/

void			init_ray(t_cub *cub, t_ray *ray);
unsigned int	horizon_texture(t_cub *cub, t_ray *ray, int dir);
unsigned int	vertical_texture(t_cub *cub, t_ray *ray, int dir);
void			hray(t_cub *cub, t_ray *ray);
void			vray(t_cub *cub, t_ray *ray);
void			skybox(t_cub *cub, t_ray *ray);
void			floorcast(t_cub *cub, t_ray *ray);
void			display(t_cub *cub);
void			raycast(t_cub *cub, t_ray *ray);

/*	----------input-----------------	*/

void			rotate(int keycode, t_player *player);
void			longitudinal(int keycode, t_player *player, char **exp);
void			lateral(int keycode, t_player *player, char **exp);
int				save_position(t_cub *cub, t_player *player, char **exp);
int				key_handle(int keycode, t_cub *cub);
int				direction(t_cub *cub);
int				release(int keycode, t_cub *cub);
int				mouse_rotation(int x, int y, t_cub *cub, t_player *player);
int				anti_ghosting(t_cub *cub);
void			create_hooks(t_cub *cub);

#endif
