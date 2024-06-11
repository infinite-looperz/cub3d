/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/09 16:11:53 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/11 16:05:18 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	move_check(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / T_SIZE;
	map_y = y / T_SIZE;
	if ((size_t)map_y >= data->map_h || (size_t)map_x >= data->map_w)
		return ;
	if (data->map_c[map_y][map_x] == '1')
		return ;
	data->plyr->real_x = x;
	data->plyr->real_y = y;
}

static void	rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->plyr->plyr_ang += data->plyr->rot_spd;
		if (data->plyr->plyr_ang > 2 * M_PI)
		{
			data->plyr->plyr_ang -= 2 * M_PI;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plyr->plyr_ang -= data->plyr->rot_spd;
		if (data->plyr->plyr_ang < 0)
		{
			data->plyr->plyr_ang += 2 * M_PI;
		}
	}
}

static void	move_wasd(t_data *data, int *x, int *y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		*x += round(cos(data->plyr->plyr_ang) * PLYR_SPD);
		*y += round(sin(data->plyr->plyr_ang) * PLYR_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		*x -= round(cos(data->plyr->plyr_ang) * PLYR_SPD);
		*y -= round(sin(data->plyr->plyr_ang) * PLYR_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		*x += round(sin(data->plyr->plyr_ang) * PLYR_SPD);
		*y -= round(cos(data->plyr->plyr_ang) * PLYR_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		*x -= round(sin(data->plyr->plyr_ang) * PLYR_SPD);
		*y += round(cos(data->plyr->plyr_ang) * PLYR_SPD);
	}
}

void	move(t_data *data)
{
	int	x;
	int	y;

	x = data->plyr->real_x;
	y = data->plyr->real_y;
	rotation(data);
	move_wasd(data, &x, &y);
	move_check(data, x, y);
}

void	player_init(t_data *data)
{
	data->plyr->real_x = data->plyr->x * T_SIZE + T_SIZE / 2;
	data->plyr->real_y = data->plyr->y * T_SIZE + T_SIZE / 2;
	data->plyr->rad_fov = FOV * M_PI / 180;
}
