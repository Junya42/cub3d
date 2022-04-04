/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 01:55:44 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/04 19:57:11 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../minilibx/mlx_int.h"

void	check_line(char *str)
{
	while (*str++)
		if (*(str - 1) == 32)
			*(str - 1) = 49;
}

int	check_valid(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_comma(char *line)
{
	int	i;

	i = 0;
	if (line[i] == ',')
		return (0);
	while (line[i])
	{
		if (line[i] == ',' && !check_valid(line[i + 1], "0123456789"))
			return (0);
		i++;
	}
	return (1);
}

int	check_num(char *line)
{
	int	i;
	int	j;
	int	checker;

	i = 0;
	checker = 0;
	while (line[i] && line[i] == 32)
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	j = i;
	while (line[i] && line[i] != '\n')
	{
		if (!check_valid(line[i], "0123456789,"))
			return (0);
		if (line[i] == ',')
			checker++;
		i++;
	}
	//printf("checker = %d\n", checker);
	if (checker == 2)
		return (check_comma(line + j));
	return (0);
}

int	check_path(char *line, int arg)
{
	int	i;
	int	fd;
	char	*tmp;

	i = 2;
	fd = -1;
	if (arg < 4)
	{
		while (line[i] && line[i] == 32)
			i++;
		if (line[i])
		{
			tmp = ft_strdup(&line[i]);
			if (!tmp)
				return (0);
			tmp[ft_strlen(tmp) - 1] = '\0';
			fd = open(tmp, O_RDONLY);
			free(tmp);
		}
		if (fd < 0 || !line[i])
		{
			if (!line[i])
				printf("No path were found in line\n");
			if (fd < 0)
			{
				printf("Invalid file descriptor\n");
				printf("given by : %s", &line[i]);
			}
			return (0);
		}
	}
	else
		return (check_num(line + 2));
	return (1);
}

int	parse_line(char *line, int arg)
{
	if (arg == 0)
		if (ft_strncmp(line, "NO ", 3) != 0)
			return (0);
	if (arg == 1)
		if (ft_strncmp(line, "SO ", 3) != 0)
			return (0);
	if (arg == 2)
		if (ft_strncmp(line, "WE ", 3) != 0)
			return (0);
	if (arg == 3)
		if (ft_strncmp(line, "EA ", 3) != 0)
			return (0);
	if (arg == 4)
		if (ft_strncmp(line, "F ", 2) != 0)
			return (0);
	if (arg == 5)
		if (ft_strncmp(line, "C ", 2) != 0)
			return (0);
	return (check_path(line, arg));
}

char	*ft_strndup(char *str, int limit)
{
	int	i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (limit + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < limit)
		tmp[i] = str[i];
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

char	*skip_line(char	*line)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != 32)
		i++;
	if (line[i])
	{
		while (line[i] && line[i] == 32)
			i++;
		if (line[i])
			return (line + i);
	}
	return (line);
}

char	**test_map(char **av)
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

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	line = NULL;
	total = ft_strdup("");
	checker = 0;
	arg = 0;
	map_start = 0;
	while (1)
	{
		if (checker == 1)
			checker++;
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (checker != 2)
		{
			if (!parse_line(line, arg++))
			{
				printf("ARG = %d\n", arg - 1);
				printf("Invalid parsing in line : %s\n", line);
				free (line);
				free(total);
				return (0);
			}
		}
		if (line[0] == 'C')
		{
			if (!map_start)
				map_start = ft_strlen(total) + ft_strlen(skip_line(line));
			checker++;
		}
		if (checker == 2)
			check_line(line);
		total = gl_strjoin(total, skip_line(line), ft_strlen(total) + ft_strlen(skip_line(line)), -1);
		if (!total)
		{
			free(line);
			free(total);
			return (NULL);
		}
		free(line);
	}
	res = NULL;
	res = ft_split(total + map_start, '\n');
	if (!res)
		return (0);
	int	x;

	x = 0;
	printf("\n<--------------------->\n");
	while (res[x])
	{
		printf("res[%d] = %s\n", x, res[x]);
		x++;
	}
	tmpdata = ft_strndup(total, map_start);
	if (!tmpdata)
		return (0);
	data = ft_split(tmpdata, '\n');
	if (!data)
		return (0);
	x = 0;
	printf("\n<---------------------->\n");
	while (data[x])
	{
		printf("data[%d] = %s\n", x, data[x]);
		x++;
	}
	free_array(data);
	//free_array(res);
	free(tmpdata);
	return (res);
}

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*imap;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	void	*iplayer;
	int		bg_r;
	int		bg_g;
	int		bg_b;
	int		mx;
	int		my;
	float	px;
	float	pdx;
	float	py;
	float	pdy;
	float	pa;
	int		released;
	int		last_pressed;
	int		press_start;
	double	sprint;
	int		end;
}			t_mlx;

void	pxl_to_img(t_mlx *ptr, float x, float y, int color)
{
	char	*tmp;

	tmp = ptr->addr + (int)(y * ptr->size_line + x * (ptr->bpp / 8));
	*(unsigned int *)tmp = color;
}

int		rgb_to_hex(int r, int g, int b)
{
	int	color;

	color = (0xff << 24) | ((r&0xff) << 16) | ((g&0xff) << 8) | (b&0xff);

	/*	explication de la ligne au dessus

	 * 	|31           24|23           16|15            8|7         bit 0|
	 +---------------+---------------+---------------+---------------+
	 |0 0 0 1 0 0 1 0|0 0 1 1 0 1 0 0|0 1 0 1 0 1 1 0|0 1 1 1 1 0 0 0|
	 +---------------+---------------+---------------+---------------+

	 Transparence			R				G				B


	 Le but est de convertir le code RGB en code Hexa mais de type int
	 pour qu'il soit compatible avec mlx_pixel_put du coup, par rapport
	 au schema au dessus
	 on place juste les valeurs correspondantes dans color en utilisant
	 directement son adresse. On shift en consequence pour placer chaque
	 valeur dans son octet correspondant */

	return (color);
}

void	draw_pixels(t_mlx *ptr, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			//mlx_pixel_put(ptr->mlx, ptr->win, i, j, color);
			pxl_to_img(ptr, (float)i, (float)j, color);
			j++;
		}
		i++;
	}
}
void	erase_player(t_mlx *ptr, float x, float y)
{
	float xmax;
	float ymax;
	float ycpy;

	xmax = x + 10;
	ymax = y + 10;
	ycpy = y;
	while (x < xmax)
	{
		y = ycpy;
		while (y < ymax)
		{
			mlx_pixel_put(ptr->mlx, ptr->win, x, y, rgb_to_hex(ptr->bg_r, ptr->bg_g, ptr->bg_b));
			y++;
		}
		x++;
	}
}

void	draw_index(int a, int b, int c, int d, int color, t_mlx *ptr)
{
	int	reset;
	
	reset = c;
	while (a < b)
	{
		c = reset;
		while (c < d)
		{
			//mlx_pixel_put(ptr->mlx, ptr->win, a, c, color);
			pxl_to_img(ptr, a, c, color);
			c++;
		}
		a++;
	}
}

void	draw_map(t_mlx *ptr, char **map, int x, int y)
{
	int	color;

	//ptr->imap = mlx_new_image(ptr->mlx, ptr->mx * 64, ptr->my * 64);
	//ptr->addr = ptr->imap->data;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				color = rgb_to_hex(191,191,191);
			else
				color = rgb_to_hex(43,43,43);
			draw_index((float)y * 64 + 1, (y + 1) * 64 - 1, (float)x * 64 + 1, (x + 1) * 64 - 1, color, ptr);
			x++;
		}
		y++;
	}
}

void	draw_direction(t_mlx *ptr, int color)
{
	float	a;
	float	b;
	float	ad;
	float	bd;
	int		i;

	a = ptr->px + 5;
	b =	ptr->py + 5;
	ad = ptr->pdx;
	bd = ptr->pdy;
	i = 1;
	while (i < 10)
	{
		mlx_pixel_put(ptr->mlx, ptr->win, a + ad * i, b + bd * i, color);
		i++;
	}
}


void	draw_player(t_mlx *ptr, int color, float x, float y)
{
	float	xmax;
	float	ymax;
	float	ycpy;

	//ptr->iplayer = mlx_new_image(ptr->mlx, ptr->mx * 64, ptr->my * 64);
	//ptr->addr = mlx_get_data_addr(ptr->iplayer, &ptr->bpp, &ptr->size_line, &ptr->endian);
	//printf("addr = %s\n", ptr->addr);
	xmax = x + 10;
	ymax = y + 10;
	ycpy = y;
	while (x < xmax)
	{
		y = ycpy;
		while (y < ymax)
		{
			//if (x == xmax -10 && y == ycpy)
			//	mlx_pixel_put(ptr->mlx, ptr->win, x + ptr->pdx, y + ptr->pdy, rgb_to_hex(229, 255, 0));
			//else
			mlx_pixel_put(ptr->mlx, ptr->win, x, y, color);
			//pxl_to_img(ptr, x, y, color);
			y++;
		}
		x++;
	}
}

int	create_window(t_mlx *ptr, char **av, char **map)
{
	ptr->mlx = mlx_init();
	if (!ptr->mlx)
		return (0);
	ptr->win = mlx_new_window(ptr->mlx, ptr->mx * 64, ptr->my * 64, "cub3d");
	if (!ptr->win)
	{
		mlx_destroy_display(ptr->mlx);
		return (0);
	}
	ptr->imap = mlx_new_image(ptr->mlx, ptr->mx * 64, ptr->my * 64);
	ptr->addr = mlx_get_data_addr(ptr->imap, &ptr->bpp, &ptr->size_line, &ptr->endian);
	ptr->bg_r = ft_atoi(av[2]);
	ptr->bg_g = ft_atoi(av[3]);
	ptr->bg_b = ft_atoi(av[4]);
	draw_pixels(ptr, rgb_to_hex(ptr->bg_r, ptr->bg_g, ptr->bg_b), ptr->mx * 64, ptr->my * 64);	//rempli la map avec la couleur choisi
	draw_map(ptr, map, 0, 0);
	draw_player(ptr, 0xff194b, ptr->px, ptr->py);	//dessine le joueur
	draw_direction(ptr, rgb_to_hex(0,214,111));
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->imap, 0, 0);
	return (1);
}

int	key_handle(int keycode, t_mlx *ptr)
{
	float	calibrageleft;
	float	calibrageright;

	if (keycode == 65505)
		ptr->sprint += 0.75;
	if (ptr->released && ptr->released != keycode)
	{
		ptr->last_pressed = keycode;
		ptr->press_start = 1;
	}
	if (!ptr->released)
		ptr->released = keycode;
	//erase_player(ptr, ptr->px, ptr->py); //efface l'ancienne pos du joueur
	//mlx_destroy_image(ptr->mlx, ptr->iplayer);
	ptr->iplayer = NULL;
	if (ptr->released != keycode)
	{
		if (ptr->released == 'w')
			ptr->py -= 5 * ptr->sprint;
		if (ptr->released == 's')
			ptr->py += 5 * ptr->sprint;
		if (ptr->released == 'a')
			ptr->px -= 5 * ptr->sprint;
		if (ptr->released == 'd')
			ptr->px += 5 * ptr->sprint;
	}
	if (keycode == 'q')
	{
		ptr->pa -= 0.1;
		if (ptr->pa < 0)
			ptr->pa += 2 * PI;
		printf("pa = %f\n", ptr->pa);
		ptr->pdx = cos(ptr->pa) * 5;
		ptr->pdy = sin(ptr->pa) * 5;
	}
	if (keycode == 'e')
	{
		ptr->pa += 0.1;
		if (ptr->pa > 2 * PI)
			ptr->pa -= 2 * PI;
		printf("pa = %f\n", ptr->pa);
		ptr->pdx = cos(ptr->pa) * 5;
		ptr->pdy = sin(ptr->pa) * 5;
	}
	if (keycode == 'w')
	{
		ptr->px += ptr->pdx;
		ptr->py += ptr->pdy;
	}
	if (keycode == 's')
	{
		ptr->px -= ptr->pdx;
		ptr->py -= ptr->pdy;
	}
	calibrageleft = ptr->pa - PI / 2;
	calibrageright = ptr->pa + PI / 2;
	if (calibrageleft < 0)
		calibrageleft += 2 * PI;
	if (calibrageright > 2 * PI)
		calibrageright -= 2 * PI;
	printf("left = %f\n", calibrageleft);
	printf("right = %f\n", calibrageright);
	if (keycode == 'a')
	{
		printf("pdx = %f\npdy = %f\n", ptr->pdx, ptr->pdy);
		ptr->px += cos(calibrageleft) * 5;
		ptr->py += sin(calibrageleft) * 5;
		//ptr->px -= 5 * ptr->sprint;
	}
	if (keycode == 'd')
	{
		ptr->px += cos(calibrageright) * 5;
		ptr->py += sin(calibrageright) * 5;
		//ptr->px += 5 * ptr->sprint;
	}
	if (keycode == 65307)
		ptr->end = 1;
	draw_player(ptr, 0xff194b, ptr->px, ptr->py); //dessine la nouvelle pos du joueur
	draw_direction(ptr, rgb_to_hex(0,214,111));
	return (1);
}

int	release(int keycode, t_mlx *ptr)	//permet le double input
{
	if (keycode == 65505)
		ptr->sprint -= 0.75;
	if (ptr->released == keycode)
	{
		ptr->released = 0;
		ptr->press_start = 0;
	}
	ptr->last_pressed = 0;
	//printf("release key = %d\n", keycode);
	//printf("released = %d\n", ptr->released);
	return (1);
}

void	usleep_(long int duration)
{
	while (duration)
	{
		usleep(duration / 10);
		duration /= 10;
	}
}

int	nullfunc(t_mlx	*ptr)	//fonction echap pour le mlx_loop_hook
{
	if (ptr->end == 1)
		mlx_destroy_window(ptr->mlx, ptr->win);
	if (!ptr->last_pressed  && ptr->press_start && ptr->released) //Permet d'appliquer le move en buffer
	{
		usleep_(30*10000);
		erase_player(ptr, ptr->px, ptr->py);
		if (ptr->released == 'w')
			ptr->py -= 5;
		if (ptr->released == 's')
			ptr->py += 5;
		if (ptr->released == 'a')
			ptr->px -= 5;
		if (ptr->released == 'd')
			ptr->px += 5;
		draw_player(ptr, 0xff194b, ptr->px, ptr->py); //dessine la nouvelle pos du joueur
	}
	return (0);
}

void	get_map_xy(char **map, t_mlx *ptr)
{
	int	y;
	int	x;
	int	max;

	y = 0;
	x = 0;
	max = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > max)
			max = x;
		y++;
	}
	ptr->mx = max;
	ptr->my = y;
}

int main(int ac, char **av)
{
	t_mlx	ptr;
	char	**map;

	if (ac == 2 || ac == 5)
	{
		if (ac == 2)
			printf("You can also give 5 arguments to launch the mlx screen\nControls are WASD for movement, Shift for sprinting, Escape to quit the game\nUsage: ./cub3d map_to_parse.ber R G B\n");
		/*	DEBUT BLOC MLX	*/

		if (ac == 5)
		{
			map = test_map(av); 
			ptr.px = 300;	//position initial joueur x
			ptr.py = 300;	//position initial joueur y
			ptr.pa = 90;
			ptr.pdx = cos(ptr.pa) * 5;
			ptr.pdy = sin(ptr.pa) * 5;
			ptr.released = 0; //permet le double input (deplacement en diagonal)
			ptr.last_pressed = 0;	//fluidifie les inputs
			ptr.press_start = 0;	//check si je suis en attente d'input dans un buffer
			ptr.sprint = 1;		//multiplicateur vitesse de deplacement
			ptr.end = 0;	//check pour la fin de jeu

			get_map_xy(map, &ptr);
			create_window(&ptr, av, map);
			mlx_loop_hook(ptr.mlx, nullfunc, &ptr);
			mlx_hook(ptr.win, KeyPress, KeyPressMask, key_handle, &ptr);
			mlx_hook(ptr.win, KeyRelease, KeyReleaseMask, release, &ptr);
			mlx_loop(ptr.mlx);
			mlx_destroy_display(ptr.mlx);
			free(ptr.mlx);
		}
		/*	FIN BLOC MLX	*/
		/* implementer des trucs a faire avec la map */
		free_array(map);
	}
	else
		printf("Wrong number of arguments, need 2 or 5\nUsage: ./cub3d map_name\nUsage MLX: ./cub3d map_name R G B\n");
	(void)ptr;
	return (0);
}
