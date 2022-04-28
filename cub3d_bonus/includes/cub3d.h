/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:35:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/28 01:32:20 by anremiki         ###   ########.fr       */
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

# define NVALUE 0.017452925
# define RAD 0.017452925

/*	-----------Parsing----------	*/

void			free_data(t_parse *parse);
int				free_and_return(t_parse *p, int flag, int exitcode);
int				is_num(char *str);
int				get_fd_size(char *filename);
int				is_charset(char c, char *set);
void			init_variable(t_parse *p);
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

/*	----------Init--------------	*/

void			get_angle(t_cub *cub, char dir);
void			get_map_xy(char **map, t_cub *cub);
int				init_cub(t_cub *cub);
int				create_window(t_cub *cub);
int				get_sprite_txt(t_cub *cub);

/* -----------Engine mod--------	*/

void			printmap(char **map);
int				check_valid(char c, char *valid);
void			modify_map(char **map, char **exp, int mult);
char			**expand(char **map, int x, int y, int mult);
void			transform(char **map, int x, int y, char c);

/*	----------textures----------	*/

int				create_imgs(t_cub *cub);
void			destroy_imgs(t_cub *cub, t_text *imgs);

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

/*	----------Shaders------------	*/

int				red(int color, float shader);
int				green(int color, float shader);
int				blue(int color, float shader);
int				shade(int color, float shader);
int				addshade(int color, float shader);
int				colorize(int base, float shader, float dim, int color);
unsigned int	case_texture(t_cub *cub, t_ray *ray);

/*	----------Pixels-------------	*/

void			spxl_to_ray(t_cub *cub, float x, float y, unsigned int color);
void			pxl_to_img(t_cub *cub, float x, float y, int flag);
void			pxl_to_ray(t_cub *cub, float x, float y, unsigned int color);
unsigned int	pxl_from_img(t_cub *cub, int x, int y, int i);
unsigned int	rgb_to_hex(unsigned int r, unsigned int g, unsigned int b);

/*	----------Sprites-------------	*/

void			sprite_casting(t_cub *cub);
void			print_sprite(t_cub *cub, t_csp *s);

/*	----------Minimap-------------	*/

void			draw_player(t_cub *cub, float x, float y);
void			draw_posmap(t_cub *cub, char **map, int x, int y);

/*	----------Raycast-------------	*/

void			init_ray(t_cub *cub, t_ray *ray);
unsigned int	horizon_texture(t_cub *cub, t_ray *ray, int dir);
unsigned int	vertical_texture(t_cub *cub, t_ray *ray, int dir);
void			hray(t_cub *cub, t_ray *ray);
void			vray(t_cub *cub, t_ray *ray);
void			skybox(t_cub *cub, t_ray *ray);
void			floorcast(t_cub *cub, t_ray *ray);
void			display(t_cub *cub, int draw);
void			raycast(t_cub *cub, t_ray *ray, int draw);

/*	----------Input-----------------	*/

void			rotate(int keycode, t_cub *cub, t_player *player);
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
