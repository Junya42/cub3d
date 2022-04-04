/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:35:18 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/04 16:46:54 by anremiki         ###   ########.fr       */
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

# define PI 3.1415926535

enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR,
	gnl_loop
};

typedef struct s_parse
{
	char	**res;
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

/* UTILS */
int		fatal_error(char *str);
void	free_string(char *s1, char *s2, char *s3);
char	*ft_strndup(char *str, int limit);
void	check_line(char *str);
int		close_fd(int fd, char *line, int i, int retvalue);
/* UTILS */

/* PARSING */
char    *skip_line(char *line);
int		exit_parsing(char *str);
void	show_parse_error(int arg, char *line);
int		check_valid_file(t_parse *parse, int fd);
int		parse_line(char *line, int arg);
int		parsing(char **av);
/* PARSING */

#endif
