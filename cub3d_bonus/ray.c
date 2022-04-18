/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 03:33:29 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/18 03:38:53 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	create_win_textures_variables(...)
{
	mlx_init();
	mlx_create_window();
	create_textures();
	get_textures_addr();
	get_player_data();
	raycasting();
}

int	auto_raycast(int keycode, struct)
{
	usleep_(...);
	raycast(struct);
}

int main()
{
	create_window_textures_variables(...);
	mlx_loop_hook(...);
	mlx_hook(mlx, KeyPress, KeyPressMask, key_handle, struct);
	mlx_hook(mlx, EventWindow, EventWindowMask, auto_raycast, struct);
	mlx_loop();
}
