/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:53:40 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/11 01:44:55 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	reset_values(t_cub *cub, t_ray *ray)
{
	ray->i = 0;
	ray->limit = 0;
	ray->hray = 1000000;
	ray->vray = 1000000;
	ray->hdir = 0;
	ray->vdir = 0;
	ray->hx = cub->x;
	ray->hy = cub->y;
	ray->vx = cub->x;
	ray->vy = cub->y;
	ray->contan = (-1 / tan(ray->ra));
	ray->ntan = (-tan(ra));
}

unsigned int	case_texture(t_cub *cub, t_ray *ray)
{
	if (ray->vray < ray->hray)
		return (vertical_texture(cub, ray, vdir));
	else
		return (horizon_texture(cub, ray, hdir));
}

void	dda_texture(t_cub *cub, t_ray *ray)
{
	if (ray->shadow > 1)
		ray->shadow = 1;
	ray->curr_px = ray->next_px * ray->offpx;
	ray->top = (int)ray->rx % 64;
	ray->bot = 64 - ray->top;
	ray->right = (int)ry % 64;
	ray->left = 64 - ray->right;
	ray->nr = ray->r * 4;
}

void	dda(t_cub *cub, t_ray *ray)
{
	if (ray->hray <= ray->vray)
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->ray = ray->hray;
	}
	else
	{
		ray->ray = ray->vray;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
	}
	ray->ray = fix_fisheye(cub->a, ray->ra, ray->ray);
	ray->raycast = (64 * VRES * cub->z / ray->ray);
	ray->next_px = 64 / raycast;
	ray->offpx = 0;
	if (raycast > VRES * cub->z + 64)
	{
		ray->offpx = (raycast - VRES * cub->z) / 2;
		ray->raycast = VRES * cub->z + 64;
	}
	ray->offset = ((HALFVRES * ptr->z) - ray->raycast / 2);
	ray->shadow = 7 / mysqrt(ray->ray);
	dda_texture(cub, ray);
}

void	raycast(t_cub *cub, t_ray *ray)
{
	init_ray(cub, ray);
	while (ray->r < NRAY)
	{
		reset_values(cub, ray);
		hray(cub, ray);
		ray->limit = 0;
		vray(cub, ray);
		dda(cub, ray);
		while (ray->i < ray->raycast)
		{
			ray->color = case_texture(cub, ray);
			pxl_to_ray(cub, ray->nr, (float)(int)(ray->i + ray->offset, ray->color));
			ray->curr_px += ray->next_px;
			ray->i++;
		}
		skybox(cub, ray);
		floorcast(cub, ray);
		secure_radians(ray->ra, ray->dra);
		ray->r++;
	}
	display(cub);
}
