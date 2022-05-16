/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:35:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/23 19:21:57 by cmarouf          ###   ########.fr       */
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
# include "../includes/define.h"
# include "../includes/struct3d.h"

/* UTILS */
void			free_data(t_parse *parse);
int				free_and_return(t_parse *p, int flag, int exitcode);
int				is_num(char *str);
int				get_fd_size(char *filename);
int				is_charset(char c, char *set);
unsigned int	rgb_to_hex(unsigned int r, unsigned int g, unsigned int b);
/* UTILS */

/* PARSING */
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
/* PARSING */

/*RAYCASTING*/
int				create_mlx(t_ray *ray);
unsigned int	get_texture_color(t_ray *ray, int y, int x, int i);
unsigned int	get_txt_color(t_ray *ray);
int				shade(int color, float shader);
void			pxl_to_ray(t_ray *ray, float x, float y, unsigned int color);
void			spxl_to_ray(t_ray *ray, float x, float y, unsigned int color);
void			pxl_to_image(t_ray *ray, int a, int c, int color);
int				count_x(char **map);
int				count_y(char **map);
float			choose_angle(char c);
void			spawn_point(t_ray *ray);
void			angle_point(t_ray *ray);
float			deg_to_rad(float angle, float degree);
float			fixfisheye(float pa, float ra, float distT);
void			raycasting(t_ray *ray);
int				key_handle(int keycode, t_ray *ray);
void			draw_floor(t_ray *ray);
void			draw_ceiling(t_ray *ray);
void			draw_raycasting(t_ray *ray, float x, float y, unsigned int c);
void			init_raycasting(t_parse *parse);
int				rayloop(t_ray *ray);
int				quit(t_ray *ray);
void			free_mlx(t_ray *ray);
void			choose_side(t_ray *ray);
void			texture_side(t_ray *ray);
void			horizontal_ray(t_ray *ray);
void			vertical_ray(t_ray *ray);
/*RAYCASTING*/

#endif
