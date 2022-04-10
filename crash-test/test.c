
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 01:55:44 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/10 23:38:52 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../minilibx/mlx_int.h"

void	draw_posmap(t_mlx *ptr, char **map, int x, int y);

void	check_line(char *str)
{
/*	while (*str++)
		if (*(str - 1) == 32)
			*(str - 1) = 49;*/
	(void)str;
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
	if (line)
		return (line);
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

/*												
 *
 *
 *
 *
 *
 *
 *
 *												*/

typedef struct s_ray
{
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	int		nray;
}			t_ray;

void	draw_player(t_mlx *ptr, int color, float x, float y);
void	usleep_(long int duration);

/*float	q_sqrt(float number)
{
	long	i;
    float	x;
	float	y;

    x = number * 0.5f;
    y  = number;
    i  = *(long*)&y;
    i  = 0x5f3759df - (i >> 1);
    y  = *(float*)&i;
    y  = y * ( 1.5f - (x * y * y));

    return (y);
}*/

float	mysqrt(float n)	//OK
{
	union
	{
		int		i;
		float	x;
	}	u;
	u.x = n;
	u.i = (1<<29) + (u.i >> 1) - (1<<22);
	u.x = u.x + n/u.x;
	u.x = 0.25f * u.x + n / u.x;
	return (u.x);
}

float	dist(float ax, float ay, float bx, float by)	//OK
{
	return (mysqrt((bx - ax) * (bx - ax) + (by -ay) * (by - ay)));
}

void	pxl_to_img(t_mlx *ptr, float x, float y, int color)	//OK
{
	char	*tmp;

	tmp = ptr->addr + (int)(y * ptr->size_line + x * (ptr->bpp / 8));
	*(unsigned int *)tmp = color;
}

void	pxl_to_ray(t_mlx *ptr, float x, float y, unsigned int color)	//OK
{
	char	*tmp;

	int size;
	int	completer;
	if (!ptr->textaddr)
		return ;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0 && x)
		y = 0;
	//printf("ptr->bsize_line%d\n", ptr->bsize_line);
	size = (int)(y * ptr->bsize_line + x * (ptr->bbpp / 8));
	if (size < 0 || size >= ptr->raysize) //(width + 32) * height * 4
		return ;
	tmp = ptr->textaddr + size;
	completer = 0;
	while (completer < 4)
	{
		*((unsigned int *)tmp + completer) = color;
		completer++;
	}
	(void)completer;
}

unsigned int	pxl_from_img(t_text *text, int x, int y, int i)	//OK
{
	char	*tmp;
	int size;

	if (y == 0 && x < 0)
		x = 0;
	if (y < 0)
		y = 0;
		//return (0xffffff);
	size = (int)(y * text[i].size + x * (text[i].bpp / 8));
	if (size < 0 || size >= 1228800)
	{
		//printf("x = %d\ny = %d\n", x, y);
		//printf("size = %d\n", size);
		return (0xffffff);
	}
	tmp = text[i].addr + size;
	//printf("pxl > %s\n", text[i].name);
	return (*(unsigned int *)tmp);
}

int		rgb_to_hex(int a, int r, int g, int b)	//OK
{
	int	color;

	color = (a&0xff << 24) | ((r&0xff) << 16) | ((g&0xff) << 8) | (b&0xff);
	return (color);
}

int	shade(int color, float shader)	//OK
{
	int	r;
	int	g;
	int	b;

	if (shader < 0)
		shader = 0;
	r = (color >> 16) * shader;
	g = ((color >> 8) & 0x00ff) * shader;
	b = (color & 0x0000ff) * shader;
	return ((0xff << 24) | ((r&0xff) << 16) | ((g&0xff) << 8) | (b&0xff));
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
			pxl_to_img(ptr, (float)i, (float)j, color);
			j++;
		}
		i++;
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
			if (!(c % 2))
			{
				mlx_pixel_put(ptr->mlx, ptr->win, a, c, color);
			}
			//pxl_to_img(ptr, a, c, color);
			c++;
		}
		a++;
	}
}

void	draw_map(t_mlx *ptr, char **map, int x, int y)
{
	int	color;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				color = rgb_to_hex(255, 191, 191, 191);
			else if (check_valid(map[y][x], "NSEW0"))
				color = rgb_to_hex(255, 43, 43, 43);
			else if (map[y][x] == '2')
				color = 0xba0047;
			else if (ft_isalpha(map[y][x]))
				color = 0x7894bf;
			else
				color = rgb_to_hex(255, 99, 14, 48);
			if (check_valid(map[y][x], "NSEW12 "))
				draw_index((float)x * 16 + 2, (x + 1) * 16 - 2, (float)y * 16 + 2, (y + 1) * 16 - 2, color, ptr);
			x++;
		}
		y++;
	}
}

void	draw_posmap(t_mlx *ptr, char **map, int x, int y)
{
	int	i;
	int	j;
	int	xmax;
	int	ogx;
	int	ogy;
	int	ymax;
	int	color;

	ogx = x;
	ogy = y;
	i = 0;
	while (i < 5)
	{
		if (x > 0)
			x--;
		else
			break ;
		i++;
	}
	xmax = ogx + 5;
	j = 0;
	while (j < 5)
	{
		if (y > 0)
			y--;
		else
			break ;
		j++;
	}
	ymax = ogy + 5;
	if (y < 0 || x < 0)
		return ;
	while (map[y] && y <= ymax)
	{
		x = xmax - 5 - i;
		while (map[y][x] && x <= xmax)
		{
			if (map[y][x] == '1')
				color = rgb_to_hex(255, 191, 191, 191);
			else if (check_valid(map[y][x], "NSEW0"))
				color = rgb_to_hex(255, 43, 43, 43);
			else if (map[y][x] == '2')
				color = 0xba0047;
			else
				color = rgb_to_hex(255, 99, 14, 48);
			if (check_valid(map[y][x], "NSEW12 "))
				draw_index((float)x * 16 + 2, (x + 1) * 16 - 2, (float)y * 16 + 2, (y + 1) * 16 - 2, color, ptr);
			x++;
		}
		y++;
	}
}

float	fix_fisheye(float pa, float ra, float ray)	//OK
{
	float	fix;

	fix = pa - ra;
	if (fix < 0)
		fix += 2 * PI;
	if (fix > 2 * PI)
		fix -= 2 * PI;
	if (!ray)
		return (0);
	return (ray * (cos(fix)));
}

float	deg_to_rad(float angle, float degree)	//OK
{
	angle += (NVALUE * degree);
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	print_hud(t_mlx *ptr, float i)
{

	if (i <= 1)
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->b1, ptr->hres / 2 - 128, ptr->vres - 78);
	if (i <= 2)
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->b2, ptr->hres / 2 - 128, ptr->vres - 78);
	if (i <= 3)
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->b3, ptr->hres / 2 - 128, ptr->vres - 78);
}

void	draw_direction(t_mlx *ptr, int color, int fov)
{
	float	rx = 0;
	float	ry = 0;
	float	ra;
	float	xo = 0;
	float	yo = 0;
	float	hray;
	float	vray;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	ray = 0;
	float	offset;
	float	raycast;
	int		mx;
	int		my;
	float	r;
	int		limit;
	int		i;
	int		vdir;
	int		hdir;
	float	pi2 = ptr->pi2;
	float	dpi = ptr->dpi;
	float	pi3 = ptr->pi3;
	float	onetan;
	float	ntan;
	float	npy = (((int)ptr->py >> 6) << 6);
	float	npx = (((int)ptr->px >> 6) << 6);
	int		scalex = ptr->hres;
	int		scaley = ptr->vres;
	int		nray;	//OK

	nray = ptr->hres / 4;
	r = 0 ;
	(void)color;
	ra = ptr->pa - (NVALUE * fov / 2);
	if (ra < 0)
		ra += dpi;
	if (ra > dpi)
		ra -= dpi;
	//printf("ra = %f\n", ra);
	//printf("ptr->pa = %f\n", ptr->pa);
	//printf("nray %d\n", nray);
	//printf("exp = %c\n", ptr->exp[(int)ptr->py][(int)ptr->px]);
	while (r < nray)
	{
		limit = 0;
		hray = 1000000;
		hdir = 0;
		vdir = 0;
		hx = ptr->px;
		hy = ptr->py;
		onetan = (-1/tan(ra));
		if (ra == PI || ra == 0)
		{
			rx = ptr->px;
			ry = ptr->py;
			limit = ptr->my;
		}
		else if (ra > PI)
		{
			hdir = 1;
			ry = npy - 0.0001;
			rx = (ptr->py - ry) * onetan + ptr->px;
			yo = -64;
			xo = -yo * onetan;
		}
		else if (ra < PI)
		{
			hdir = 2;
			ry = npy + 64;
			rx = (ptr->py - ry) * onetan + ptr->px;
			yo = 64;
			xo = -yo * onetan;
		}
		while (limit < 20) // < ptr->my
		{
			mx = (int)(rx);
			my = (int)(ry);
			if ((mx < ptr->ex && my < ptr->ey && mx > -1 && my > -1) && check_valid(ptr->exp[my][mx], "12DPLlr"))
			{
				if (ptr->exp[my][mx] == '2')
				{
					hdir += 2;
					if ((mx + ptr->paintings) % 3 == 0 && hdir == 4)
						hdir += 2;
				}
				//if (r == nray / 2)
				//	printf("vexp = %c\n", ptr->exp[my][mx]);
				hx = rx;
				hy = ry;
				hray = dist(ptr->px, ptr->py, hx, hy);
				break ;
			}
			else
			{
				rx += xo;
				ry += yo;
				limit++;
			}
		}
		limit = 0;
		vray = 1000000;
		vx = ptr->px;
		vy = ptr->py;
		ntan = (-tan(ra));
		if (ra == PI || ra == 0)
		{
			rx = ptr->px;
			ry = ptr->py;
			limit = ptr->my;
		}
		else if (ra > pi2 && ra < pi3)
		{
			vdir = 1;
			rx = npx - 0.0001;
			ry = (ptr->px - rx) * ntan + ptr->py;
			xo = -64;
			yo = -xo * ntan;
		}
		else if (ra < pi2 || ra > pi3)
		{
			vdir = 2;
			rx = npx + 64;
			ry = (ptr->px - rx) * ntan + ptr->py;
			xo = 64;
			yo = -xo * ntan;
		}
		while (limit < 20) // < ptr->my
		{
			mx = (int)(rx);
			my = (int) (ry);
			if ((mx < ptr->ex && my < ptr->ey && mx > -1 && my > -1) && check_valid(ptr->exp[my][mx], "12DPLlr"))
			{
				if (ptr->exp[my][mx] == '2')
					vdir += 2;
				//if (check_valid(ptr->exp[my][mx], "Pllr"))
				//	vdir += 2;
				//if (r == 30)
				//	printf("vexp = %c\n", ptr->exp[my][mx]);
				vx = rx;
				vy = ry;
				vray = dist(ptr->px, ptr->py, vx, vy);
				break ;
			}
			else
			{
				rx += xo;
				ry += yo;
				limit++;
			}
		}
		if (vray < hray)
		{
			rx = vx;
			ry = vy;
			ray = vray;
		}
		if (hray < vray)
		{
			rx = hx;
			ry = hy;
			ray = hray;
		}
		ray = fix_fisheye(ptr->pa, ra, ray);
		raycast = (64 * scaley * ptr->pz / ray);
		float	next_px = 64 / raycast;
		float	offpx = 0;
		if (raycast > scaley * ptr->pz + 64)
		{
			offpx = (raycast - scaley * ptr->pz) / 2;
			raycast = scaley * ptr->pz + 64;
		}
		//offset = ((scaley / 2) - raycast / 2) * ptr->pz;
		offset = ((scaley * ptr->pz / 2)- raycast / 2);
		i = 0;
		float	shadow;

		shadow = 7/mysqrt(ray);
		if (shadow > 1)
			shadow = 1;
		unsigned int tcolor = 0;
		float	case1 = (int)ry % 64;
		float	case2 = 64 - case1;
		float	case3 = (int)rx % 64;
		float	case4 = 64 - case3;
		float	current_px = next_px * offpx;
		(void)scalex;
		float	nr = r * 4;
		int		skycolor;
		while (i < raycast)
		{
			if (vray < hray)
			{
				if (vdir == 1)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case1, 0), shadow);
				if (vdir == 2)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case2, 1), shadow);
				if (vdir == 3)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case1, 4), shadow - 0.3);
				if (vdir == 4)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case2, 4), shadow - 0.3) ;
			}
			if (hray < vray)
			{
				if (hdir == 1)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case3, 2), shadow);
				if (hdir == 2)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case4, 3), shadow);
				if (hdir == 3)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case3, 4), shadow);
				if (hdir == 4)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case4, 4), shadow);
				if (hdir == 5)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case3, 7), shadow);
				if (hdir == 6)
					tcolor = shade(pxl_from_img(ptr->text, current_px, case4, 7), shadow);
			}
			pxl_to_ray(ptr, (nr), (float)(int)(i + (offset)), tcolor);
			current_px += next_px;
			i++;
		}
		i = 0;
		while (i < offset)
		{
			skycolor = pxl_from_img(ptr->text, i, ra * 180 / PI, 6);
			if (i > offset - 8)
				pxl_to_ray(ptr, nr, i, skycolor);
			else
				pxl_to_ray(ptr, nr, i, skycolor);
			i++;
		}

		int	j = offset + raycast;	//Debut au bas du mur
		float	jlimit;
		while (j < scaley)	//On parcourt du bas du mur jusqu'au bas de la fenetre
		{
			jlimit = j - (scaley * ptr->pz / 2);	//L'ecart de hauteur entre le point j et la hauteur de vision du joueur
			current_px = ptr->px / 2 + cos(ra) * 200 * 64 / jlimit / fix_fisheye(ptr->pa, ra, 1); //x
			next_px = ptr->py / 2 + sin(ra) * 200 * 64 / jlimit / fix_fisheye(ptr->pa, ra, 1);	//y
			tcolor = shade(pxl_from_img(ptr->text, (int)next_px % 64, (int)current_px % 64, 5), shadow);
			pxl_to_ray(ptr, nr, j, tcolor);
			j++;
		}
		ra += ptr->dra;
		if (ra < 0)
			ra += dpi;
		if (ra > dpi)
			ra -= dpi;
		r += 1;
		(void)nr;
		(void)skycolor;
	}
	//printf("ra = %f\n", ra);
	ptr->magic++;
	//mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->imap, 0, 0);
	//draw_player(ptr, 0x7b00ff, (ptr->px - 3) / 64 * 16, (ptr->py - 3) / 64* 16);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->iplayer, 0, 0);
	//mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->hud[0].hud, ptr->hres / 2 - 128, ptr->vres - 78);
	print_hud(ptr, ptr->anim);
	//draw_posmap(ptr, ptr->map, ((int)ptr->px >> 6), ((int)ptr->py >> 6));
	//mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->imap, 0, 0);
	//draw_player(ptr, 0x7b00ff, (ptr->px - 3) / 64 * 16, (ptr->py - 3) / 64* 16);
	//draw_cast(ptr, rgb_to_hex(255, 255, 0, 255), 60);
	//mlx_draw_line(ptr->mlx, ptr->win, a, b, a + ad * i, b + bd * i, color);
	//printf("hitpos ry = %f >>> hitpos rx = %f\n", ry, rx);
	//tan = cos(pa) / sin(pa)
	//tan = pdx / pdy
	//printf("py = %f >>> px = %f\n", b, a);
	//printf("ray = %f >>> player = %f\n", (tota) - (totb), (a) - (b));
	//if (check_NS(b + bd * i, 64))
	//		ptr->color = 0xff194b;
	//	else
	//	ptr->color = rgb_to_hex(255, 0, 219, 150);
}

void	draw_player(t_mlx *ptr, int color, float x, float y)
{
	float	xmax;
	float	ymax;
	float	ycpy;

	xmax = x + 7;
	ymax = y + 7;
	ycpy = y;
	while (x < xmax)
	{
		y = ycpy;
		while (y < ymax)
		{
			mlx_pixel_put(ptr->mlx, ptr->win, x, y, color);
			y++;
		}
		x++;
	}
}

void	create_hud(t_mlx *ptr)
{
	int	a;
	int	b;

	ptr->b1 = mlx_xpm_file_to_image(ptr->mlx, "./textures/blooda.xpm", &a, &b);
	ptr->b2 = mlx_xpm_file_to_image(ptr->mlx, "./textures/bloodb.xpm", &a, &b);
	ptr->b3 = mlx_xpm_file_to_image(ptr->mlx, "./textures/bloodc.xpm", &a, &b);
}

t_text	*create_imgs(t_mlx *ptr)
{
	t_text *text;
	//printf("OTHER FUNCrbpp = %d > rsize = %d > rendian = %d\n", ptr->bbpp, ptr->bsize_line, ptr->bendian);
	text = (t_text *)malloc(sizeof(t_text) * 9);
	if (!text)
	{
		printf("Memory allocation failed for images\n");
		return (NULL);
	}
	text[0].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/bookshelf.xpm", &text[0].a, &text[0].b);
	text[0].addr = mlx_get_data_addr(text[0].texture, &text[0].bpp, &text[0].size, &text[0].end);
	text[1].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/birch_planks.xpm", &text[1].a, &text[1].b);
	text[1].addr = mlx_get_data_addr(text[1].texture, &text[1].bpp, &text[1].size, &text[1].end);
	text[2].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/blackstone.xpm", &text[2].a, &text[2].b);
	text[2].addr = mlx_get_data_addr(text[2].texture, &text[2].bpp, &text[2].size, &text[2].end);
	text[3].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/bricks.xpm", &text[3].a, &text[3].b);
	text[3].addr = mlx_get_data_addr(text[3].texture, &text[3].bpp, &text[3].size, &text[3].end);
	text[4].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/pblackstone.xpm", &text[4].a, &text[4].b);
	text[4].addr = mlx_get_data_addr(text[4].texture, &text[4].bpp, &text[4].size, &text[4].end);
	text[5].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/doomfloor.xpm", &text[5].a, &text[5].b);
	text[5].addr = mlx_get_data_addr(text[5].texture, &text[5].bpp, &text[5].size, &text[5].end);
	text[6].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/skyrev.xpm", &text[6].a, &text[6].b);
	text[6].addr = mlx_get_data_addr(text[6].texture, &text[6].bpp, &text[6].size, &text[6].end);
	text[7].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/tabdeath.xpm", &text[7].a, &text[7].b);
	text[7].addr = mlx_get_data_addr(text[7].texture, &text[7].bpp, &text[7].size, &text[7].end);
	text[8].texture = mlx_xpm_file_to_image(ptr->mlx, "./textures/mapbg.xpm", &text[8].a, &text[8].b);
	text[8].addr = mlx_get_data_addr(text[8].texture, &text[8].bpp, &text[8].size, &text[8].end);
	return (text);
}


void	destroy_imgs(t_mlx *ptr, t_text *imgs, int i)
{
	while (i < ptr->n_imgs)
	{
		mlx_destroy_image(ptr->mlx, imgs[i].texture);
		i++;
	}
	mlx_destroy_image(ptr->mlx, ptr->imap);
	mlx_destroy_image(ptr->mlx, ptr->iplayer);
}

int	create_window(t_mlx *ptr, char **map)
{
	ptr->mlx = mlx_init();
	if (!ptr->mlx)
		return (0);
	ptr->win = mlx_new_window(ptr->mlx, ptr->hres, ptr->vres, "cub3d");
	if (!ptr->win)
	{
		mlx_destroy_display(ptr->mlx);
		return (0);
	}
	ptr->imap = mlx_new_image(ptr->mlx, 9 * 16, 9 * 16);
	ptr->addr = mlx_get_data_addr(ptr->imap, &ptr->bpp, &ptr->size_line, &ptr->endian);
	ptr->iplayer = mlx_new_image(ptr->mlx, ptr->hres, ptr->vres);
	ptr->textaddr = mlx_get_data_addr(ptr->iplayer, &ptr->bbpp, &ptr->bsize_line, &ptr->bendian);
	ptr->text = create_imgs(ptr);
	create_hud(ptr);
	draw_posmap(ptr, map, ((int)ptr->px >> 6), ((int)ptr->py >> 6));
	draw_direction(ptr, rgb_to_hex(255, 0,214,111), ptr->fov);
	return (1);
}

int	key_handle(int keycode, t_mlx *ptr)
{
	float	calibrageleft;
	float	calibrageright;
	int		dash;
	float	cpy;

	cpy = ptr->sprint;
	dash = 0;
	if (keycode == 65505)
		ptr->sprint = 1.7;
	if (keycode == 65507)
	{
		ptr->sprint += 5; 
		dash = 1;
	}
	if (ptr->released && ptr->released != keycode)
	{
		ptr->last_pressed = keycode;
		ptr->press_start = 1;
	}
	if (!ptr->released)
		ptr->released = keycode;
	/*	draw_direction(ptr, rgb_to_hex(255, 0,214,111), ptr->fov);	*/
	if (ptr->released != keycode)
	{
		if (ptr->released == 65505)
			ptr->sprint = 1.7;
		if (!dash)
			cpy = ptr->sprint;
		if (ptr->released == 'q')
		{
			ptr->pa -= 0.07;
			if (ptr->pa < 0)
				ptr->pa += ptr->dpi;
			ptr->pdx = cos(ptr->pa) * 5;
			ptr->pdy = sin(ptr->pa) * 5;
		}
		if (ptr->released == 'e')
		{
			ptr->pa += 0.07;
			if (ptr->pa > ptr->dpi)
				ptr->pa -= ptr->dpi;
			ptr->pdx = cos(ptr->pa) * 5;
			ptr->pdy = sin(ptr->pa) * 5;
		}
		if (ptr->released == 'w')
		{
			ptr->px += ptr->pdx * ptr->sprint;
			ptr->py += ptr->pdy * ptr->sprint;
		}
		if (ptr->released == 's')
		{
			ptr->px -= ptr->pdx * ptr->sprint;
			ptr->py -= ptr->pdy * ptr->sprint;
		}
		calibrageleft = ptr->pa - ptr->pi2;
		calibrageright = ptr->pa + ptr->pi2;
		if (calibrageleft < 0)
			calibrageleft += ptr->dpi;
		if (calibrageright > ptr->dpi)
			calibrageright -= ptr->dpi;
		if (ptr->released == 'a')
		{
			ptr->px += cos(calibrageleft) * 5 * ptr->sprint;
			ptr->py += sin(calibrageleft) * 5 * ptr->sprint;
		}
		if (ptr->released == 'd')
		{
			ptr->px += cos(calibrageright) * 5 * ptr->sprint;
			ptr->py += sin(calibrageright) * 5 * ptr->sprint;
		}
	}
	if (keycode == 'q')
	{
		ptr->pa -= 0.07;
		if (ptr->pa < 0)
			ptr->pa += ptr->dpi;
		ptr->pdx = cos(ptr->pa) * 5;
		ptr->pdy = sin(ptr->pa) * 5;
	}
	if (keycode == 'e')
	{
		ptr->pa += 0.07;
		if (ptr->pa > ptr->dpi)
			ptr->pa -= ptr->dpi;
		ptr->pdx = cos(ptr->pa) * 5;
		ptr->pdy = sin(ptr->pa) * 5;
	}
	if (keycode == 'w')
	{
		ptr->px += ptr->pdx * ptr->sprint;
		ptr->py += ptr->pdy * ptr->sprint;
	}
	if (keycode == 's')
	{
		ptr->px -= ptr->pdx * ptr->sprint;
		ptr->py -= ptr->pdy * ptr->sprint;
	}
	calibrageleft = ptr->pa - ptr->pi2;
	calibrageright = ptr->pa + ptr->pi2;
	if (calibrageleft < 0)
		calibrageleft += ptr->dpi;
	if (calibrageright > ptr->dpi)
		calibrageright -= ptr->dpi;
	if (keycode == 'a')
	{
		ptr->px += cos(calibrageleft) * 5 * ptr->sprint;
		ptr->py += sin(calibrageleft) * 5 * ptr->sprint;
	}
	if (keycode == 'd')
	{
		ptr->px += cos(calibrageright) * 5 * ptr->sprint;
		ptr->py += sin(calibrageright) * 5 * ptr->sprint;
	}
	if (keycode == 65307)
		ptr->end = 1;
	ptr->sprint = cpy;
	/*	draw_direction(ptr, rgb_to_hex(255, 0,214,111), ptr->fov);	*/
	return (1);
}

int	release(int keycode, t_mlx *ptr)	//permet le double input
{
	if (keycode == 65505)
	{
		printf("end sprint\n");
		ptr->sprint = 1;
	}
	if (ptr->released == keycode)
	{
		ptr->released = 0;
		ptr->press_start = 0;
	}
	ptr->last_pressed = 0;
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
	int	calibrageleft;
	int	calibrageright;
	//mlx_mouse_move(ptr->mlx, ptr->win, ptr->hres >> 1, ptr->vres >> 1);
	if (ptr->end == 1)
		mlx_destroy_window(ptr->mlx, ptr->win);
	if (!ptr->last_pressed  && ptr->press_start && ptr->released) //Permet d'appliquer le move en buffer
	{
		usleep_(30*10000);
		if (ptr->released == 'q')
		{
			ptr->pa -= 0.07;
			if (ptr->pa < 0)
				ptr->pa += 2 * PI;
			ptr->pdx = cos(ptr->pa) * 5;
			ptr->pdy = sin(ptr->pa) * 5;
		}
		if (ptr->released == 'e')
		{
			ptr->pa += 0.07;
			if (ptr->pa > 2 * PI)
				ptr->pa -= 2 * PI;
			ptr->pdx = cos(ptr->pa) * 5;
			ptr->pdy = sin(ptr->pa) * 5;
		}
		if (ptr->released == 'w')
		{
			ptr->px += ptr->pdx;
			ptr->py += ptr->pdy;
		}
		if (ptr->released == 's')
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
		if (ptr->released == 'a')
		{
			ptr->px += cos(calibrageleft) * 5;
			ptr->py += sin(calibrageleft) * 5;
		}
		if (ptr->released == 'd')
		{
			ptr->px += cos(calibrageright) * 5;
			ptr->py += sin(calibrageright) * 5;
		}
		/*	draw_direction(ptr, rgb_to_hex(255, 0,214,111), ptr->fov);	*/
	}
	else
		usleep_(32000);
	draw_direction(ptr, rgb_to_hex(255, 0,214,111), ptr->fov);
	ptr->anim += 0.2;
	if (ptr->anim >= 3)
		ptr->anim = 0;
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

int	adjacent(t_mlx *ptr, int x, int y)
{
	char **map;

	map = ptr->map;
	if (y > 0 && map[y - 1][x] == '2')
		return (1);
	if (y + 1< ptr->my && map[y + 1][x] == '2')
		return (1);
	if (x > 0 && map[y][x - 1] == '2')
		return (1);
	if (x + 1 < ptr->mx && map[y][x + 1] == '2')
		return (1);
	return (0);
}

void	change_map(t_mlx *ptr)
{
	int		x;
	int		y;
	char	**map;

	map = ptr->map;
	y = 0;
	x = 0;
	while (map[y][x] && map[y][x] == 32)
		x++;
	map[y][x] = '2';
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1' && adjacent(ptr, x, y))
			{
				map[y][x] = '2';
				x = 0;
			}
			x++;
		}
		y++;
	}
}

void	fixed_mlx_hide(Display *mlx, t_win_list	*win)
{
	XFixesHideCursor(mlx, win->window);
	XFlush(mlx);
}
int	mouse_buttons(int keycode, t_mlx *ptr)
{
	if (keycode == 1)
		printf("Left click\n");
	if (keycode == 3)
		printf("Right Click\n");
	if (keycode == 4)
		printf("Scrolling up\n");
	if (keycode == 5)
		printf("Scrolling down\n");
	(void)ptr;
	return (0);
}

/*void	rotate_right(int x, int y, int diff, t_mlx *ptr)
  {

  }

  void	rotate_left(int x, int y, int diff, t_mlx *ptr)
  {

  }*/

int	mouse_rotation(int x, int y, t_mlx *ptr)
{
	//	int	diff;

	//	diff = abs(ptr->mouse.x - x);
	if (x < ptr->hres >> 1)
	{
		ptr->pa -= 0.002;
		if (ptr->pa < 0)
			ptr->pa += 2 * PI;
		ptr->pdx = cos(ptr->pa) * 5;
		ptr->pdy = sin(ptr->pa) * 5;
	}
	if (x > ptr->hres >> 1)
	{
		ptr->pa += 0.002;
		if (ptr->pa > 2 * PI)
			ptr->pa -= 2 * PI;
		ptr->pdx = cos(ptr->pa) * 5;
		ptr->pdy = sin(ptr->pa) * 5;
	}
	if (x < (int)(ptr->hres * 0.3) || x > (int)(ptr->hres * 0.7))
		mlx_mouse_move(ptr->mlx, ptr->win, ptr->hres >> 1, ptr->vres >> 1);
	else if (y < (int)(ptr->vres * 0.3) || y > (int)(ptr->vres * 0.7))
		mlx_mouse_move(ptr->mlx, ptr->win, ptr->hres >> 1, ptr->vres >> 1);
	/*if (y < ptr->vres >> 1)
	  {

	  }
	  if (y > ptr->vres >> 1)
	  {

	  }*/
	//mlx_mouse_move(ptr->mlx, ptr->win, ptr->hres >> 1, ptr->vres >> 1);
	(void)ptr;
	(void)y;
	return (0);
}

void	create_hooks(t_mlx *ptr)
{
	//fixed_mlx_hide(ptr->mlx, ptr->win);
	//mlx_mouse_hide(ptr->mlx, ptr->win);
	//mlx_mouse_move(ptr->mlx, ptr->win, ptr->hres >> 1, ptr->vres >> 1);
	mlx_hook(ptr->win, KeyPress, KeyPressMask, key_handle, ptr);
	mlx_hook(ptr->win, KeyRelease, KeyReleaseMask, release, ptr);
	//mlx_hook(ptr->win, 4, 0x4, mouse_buttons, ptr);
	//mlx_hook(ptr->win, 6, 0x40, mouse_rotation, ptr);
}

int main(int ac, char **av)
{
	t_mlx	ptr;
	//t_ray	ray;
	int		i;
	int		j;
	char	dir = 'i';

	i = 0;
	if (ac == 2 || ac == 5)
	{
		if (ac == 2)
			printf("You can also give 5 arguments to launch the mlx screen\nControls are WASD for movement, Shift for sprinting, Escape to quit the game\nUsage: ./cub3d map_to_parse.ber R G B\n");
		/*	DEBUT BLOC MLX	*/

		if (ac == 5)
		{
			ptr.map = test_map(av); 
			if (!ptr.map)
				return (0);
			while (ptr.map[i])
			{
				j = 0;
				while (ptr.map[i][j])
				{
					if (check_valid(ptr.map[i][j], "NWSE"))
					{
						dir = ptr.map[i][j];
						ptr.px = j * 64 + 32;	//position initial joueur x
						ptr.py = i * 64 + 32;	//position initial joueur y
						ptr.i = j;
						ptr.j = i;
						printf("dir = %c\n", dir);
						break;
					}
					j++;
				}
				i++;
			}
			printf("i = %d\nj = %d\n", i, j);
			printf("px = %f\npy = %f\n", ptr.px, ptr.py);
			if (dir == 'N')
				ptr.pa = 4.71238;
			else if (dir == 'E')
				ptr.pa = 0;
			else if (dir == 'S')
				ptr.pa = PI / 2;
			else if (dir == 'W')
				ptr.pa = PI;
			else
				ptr.pa = 4.71238;
			ptr.pdx = cos(ptr.pa) * 5;
			ptr.pdy = sin(ptr.pa) * 5;
			ptr.pi2 = PI / 2;
			ptr.dpi = 2 * PI;
			ptr.pi3 = 3 * PI / 2;
			ptr.pz = 1;
			ptr.magic = 1;
			ptr.anim = 0;
			ptr.paintings = 0;
			ptr.released = 0; //permet le double input (deplacement en diagonal)
			ptr.last_pressed = 0;	//fluidifie les inputs
			ptr.press_start = 0;	//check si je suis en attente d'input dans un buffer
			ptr.sprint = 1;		//multiplicateur vitesse de deplacement
			ptr.end = 0;	//check pour la fin de jeu
			//ptr.ray = &ray;
			ptr.fov = 90;
			//ptr.hres = 1024;
			//ptr.vres = 512;
			ptr.hres = 1280;
			ptr.vres = 720;
			ptr.n_imgs = 9;
			ptr.dra = deg_to_rad(0, ptr.fov) / (ptr.hres / 4);
			ptr.raysize = (ptr.hres + 32) * ptr.vres * 4;
			get_map_xy(ptr.map, &ptr);
			change_map(&ptr);
			ptr.exp = expand(ptr.map, ptr.mx, ptr.my, 64);
			if (!ptr.exp)
				return (0);
			modify_map(ptr.map, ptr.exp, 64);
			ptr.ex = ptr.mx * 64;
			ptr.ey = ptr.my * 64;
			//printmap(ptr.exp);
			ptr.imgsize = ((ptr.mx * 64) + 32) * (ptr.my * 64) * 4;
			printf("size = %d\n", ptr.imgsize);
			//ptr.pixmap = expandmap(ptr, ptr.map);
			create_window(&ptr,ptr.map);
			//mlx_hook(ptr.win, 6, 0x40, mouse_rotation, &ptr);
			create_hooks(&ptr);
			mlx_loop_hook(ptr.mlx, nullfunc, &ptr);
			mlx_loop(ptr.mlx);
			destroy_imgs(&ptr, ptr.text, 0);
			mlx_destroy_display(ptr.mlx);
			free(ptr.text);
			free(ptr.mlx);
			free_array(ptr.map);
			free_array(ptr.exp);
		}
		/*	FIN BLOC MLX	*/
		/* implementer des trucs a faire avec la map */
	}
	else
		printf("Wrong number of arguments, need 2 or 5\nUsage: ./cub3d map_name\nUsage MLX: ./cub3d map_name R G B\n");
	return (0);
}
