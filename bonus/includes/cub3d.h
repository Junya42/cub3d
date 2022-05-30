/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:35:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/30 18:39:36 by anremiki         ###   ########.fr       */
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
# include <sys/time.h>
# include <math.h>
# include "SDL.h"
# include "SDL_mixer.h"
# include "../minilibx/mlx.h"
# include "/usr/include/X11/X.h"
# include "../libft/includes/libft.h"
# include "struct3d.h"
# include "define.h"

# define NVALUE 0.017452925
# define RAD 0.017452925

/*	-----------Parsing----------	*/

int				free_data(t_parse *parse);
int				free_and_return(t_parse *p, int flag, int exitcode);
int				is_num(char *str);
int				get_fd_size(int saved_fd, char *filename, int len);
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
void	        get_height_width(t_parse *parse, char **map);
void	        get_expanded_height_width(t_cub *cub, char **map);
int	            check_char_rf(char **map, char *set);
int	            check_width_height(char *name, char **map, t_parse *p);
int             check_wrong_placement(char **floor, t_parse *p);
int	            check_all_rules(t_parse *p, char **rw_map);
int	            check_door(char **map);
int	            closed_door(int y, int x, char **map);
int             bonus_side(char **mcontent);
int             bonus_direction(char *side, t_parse *p);

/*	----------Init--------------	*/

void			get_angle(t_cub *cub, char dir);
void			get_map_xy(char **map, t_cub *cub);
int				init_cub(t_cub *cub, t_parse *parse);
int				create_window(t_cub *cub, t_parse *parse);
int	            quit(t_cub *cub);


/*	----------Chunks------------	*/

void			free_matrix(int ***matrix, int b, int c);
int				***err_matrix(char *error);
int				***allocate_matrix(int a, int b, int c);
void			lighthray(t_cub *cub, t_light *light, t_ray *ray, int flag);
void			lightvray(t_cub *cub, t_light *light, t_ray *ray, int flag);
void			chunk(t_cub *cub, t_light *light, t_ray *ray);
t_light			*create_lights(t_cub *cub, t_sp *sp);
int				light(t_cub *cub, t_light *light, t_ray *ray, int ***matrix);

/* -----------Engine mod--------	*/

void			printmap(char **map);
int				check_valid(char c, char *valid);
void			modify_map(char **map, char **exp, int mult);
char			**expand(char **map, int x, int y, int mult);
void			transform(char **map, int x, int y, char c);
int             close_game(t_cub *cub, t_parse *parse);

/*	----------textures----------	*/

int				create_imgs(t_cub *cub, t_parse *parse);
void			destroy_imgs(t_cub *cub, t_text *imgs);
void	        init_null(t_cub *cub, t_text *t);

/*	----------Animation----------	*/

void			jump(t_cub *cub);
void			floating(t_cub *cub);
void			animation(t_cub *cub);
int				proximity(t_cub *cub, int x, int y, int dir);
void			open_door(t_cub *cub, int adj);

/*	----------utils--------------	*/
/*	MATHS	*/
float			mysqrt(float n);
float			dist(float ax, float ay, float bx, float by);
float			fix_fisheye(float pa, float ra, float ray);
float			secure_radians(float angle, float delta);
float			deg_to_rad(float angle, float degree);
float			degree_convert(float angle);
int				quadrant_direction(float angle);
/*	MAP	*/
void	        free_mlx(t_cub *cub);
int				adjacent(t_cub *cub, int x, int y, char c);
int				adjacent_exp(t_cub *cub, int x, int y, char c);
void			update_hitbox(t_cub *cub, int x, int y, char **map);
void			change_map(t_cub *cub, t_parse *parse);
int				wipe_data(t_cub *cub, t_parse *parse);
void	        init_struct_null(t_cub *cub);
/*	TIME	*/
long long	    timestamp(void);
void	        usleep_(long int time);

/*	----------Shaders------------	*/

unsigned int	red(unsigned int color, float shader);
unsigned int	green(unsigned int color, float shader);
unsigned int	blue(unsigned int color, float shader);
unsigned int	shade(unsigned int color, float shader);
unsigned int	addshade(unsigned int color, float shader);
unsigned int	colorize(unsigned int base, float shader, float dim, int color);
unsigned int	case_texture(t_cub *cub, t_ray *ray);

/*	----------Pixels-------------	*/

void			spxl_to_ray(t_cub *cub, float x, float y, unsigned int color);
void			pxl_to_img(t_cub *cub, float x, float y, int flag);
void			pxl_to_ray(t_cub *cub, float x, float y, unsigned int color);
unsigned int	pxl_from_img(t_cub *cub, int x, int y, int i);
unsigned int	pxl_skybox(t_cub *cub, int x, int y, int i);
unsigned int	rgb_to_hex(unsigned int r, unsigned int g, unsigned int b);

/*	----------Sprites-------------	*/

int	            get_sprite_txt(t_cub *cub, int i);
int				create_sprites(t_cub *cub);
void			get_nb_sprites(t_cub *cub);
char			search_type(t_cub *cub);
int	            give_sprite_texture(t_sp *sp, t_cub *cub);
int				txt_light(t_sp *sp, t_cub *cub);
int				txt_light_red(t_sp *sp, t_cub *cub);
int				txt_light_green(t_sp *sp, t_cub *cub);
int				txt_light_blue(t_sp *sp, t_cub *cub);
int				txt_light_cyan(t_sp *sp, t_cub *cub);
int				txt_light_purple(t_sp *sp, t_cub *cub);
int				txt_light_yellow(t_sp *sp, t_cub *cub);
int	            choose_sprite_texture(t_sp *sp, t_cub *cub);
void			sprite_casting(t_cub *cub, t_light *light);
void			print_sprite(t_cub *cub, t_csp *s);
int	            choose_sprite_texture(t_sp *sp, t_cub *cub);
int	            choose_light_texture(t_sp *sp, t_cub *cub);
void	        get_sound_id(t_cub *cub, t_light *lights, float x, float y);

/*	----------Sound-------------	*/
int	    		init_audio(t_cub *cub, int i);
void			foot_steps(t_cub *cub, t_player *player);

/*	----------Minimap-------------	*/

void			draw_player(t_cub *cub, float x, float y);
void			draw_posmap(t_cub *cub, char **map, int x, int y);

/*	----------Raycast-------------	*/

void			init_ray(t_cub *cub, t_ray *ray);
void			reset_values(t_cub *cub, t_ray *ray);
unsigned int	horizon_texture(t_cub *cub, t_ray *ray, int dir);
unsigned int	vertical_texture(t_cub *cub, t_ray *ray, int dir);
void			hdist(t_cub *cub, t_ray *ray, int flag);
void			vdist(t_cub *cub, t_ray *ray, int flag);
int				hdoor(t_cub *cub, t_ray *ray);
int				vdoor(t_cub *cub, t_ray *ray);
void			hray(t_cub *cub, t_ray *ray);
void			vray(t_cub *cub, t_ray *ray);
void			compare_dist(t_cub *cub, t_ray *ray, int flag);
void			skybox(t_cub *cub, t_ray *ray);
void			floorcast(t_cub *cub, t_ray *ray);
void			display(t_cub *cub, int draw);
void			raycast(t_cub *cub, t_ray *ray);

/*	--------FloorxCeil--------------	*/

void			ceiling(t_cub *cub, t_ray *ray);
void			glass(t_cub *cub, float x, float y, float lvl);
void			init_floorcast(t_cub *cub, t_ray *ray, t_cast *c);

/*	----------Input-----------------	*/

void			slide(t_cub *cub, float x, float y, char **exp);
void			rotate(int keycode, t_cub *cub, t_player *player);
void			longitudinal(int keycode, t_player *player, char **exp, t_cub *cub);
void			lateral(int keycode, t_player *player, char **exp, t_cub *cub);
int				save_position(t_cub *cub, t_player *player, char **exp);
int				key_handle(int keycode, t_cub *cub);
int				direction(t_cub *cub);
int				release(int keycode, t_cub *cub);
int				mouse_rotation(int x, int y, t_cub *cub);
int				anti_ghosting(t_cub *cub);
void			create_hooks(t_cub *cub);

#endif
