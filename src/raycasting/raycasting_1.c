/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 16:37:28 by seyildir      #+#    #+#                 */
/*   Updated: 2024/06/04 22:54:59 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pixel_put(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < D_W && y >= 0 && y < D_H)
		mlx_put_pixel(data->img, x, y, color);
}

uint32_t	get_color(t_data *data, int direction, int x, int y)
{
	if (x < 0)
		x = 0;
	if (x >= (int)data->map_looks.txtr_t[direction]->width)
		x = data->map_looks.txtr_t[direction]->width - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)data->map_looks.txtr_t[direction]->height)
		y = data->map_looks.txtr_t[direction]->height - 1;
	return(data->map_looks.txtr_colors[direction][y][x]);
}

void	put_lines(t_data *data, int line, double dist, int direction)
{
	double	bot;
	double	top;
	double	size;
	double	fc;
	double	step;
	double		tex_y;
	double		tex_x;
	

	dist *= cos(fix_angle(data->plyr->ray_ang - data->plyr->plyr_ang));
	size = (T_SIZE / dist) * ((D_W / 2) / tan(data->plyr->rad_fov / 2));
	top = (D_H / 2) - (size / 2);
	bot = (D_H / 2) + (size / 2);
	if (top < 0)
		top = 0;
	if (bot > D_H)
		bot = D_H;
	fc = 0;
	step = (double)data->map_looks.txtr_t[direction]->height / size;
	if (data->plyr->flag == 1)
		tex_x = fmod((data->plyr->horizontal_x * ((float)data->map_looks.txtr_t[direction]->width / T_SIZE)), data->map_looks.txtr_t[direction]->width);
	else
		tex_x = fmod((data->plyr->vertical_y * ((float)data->map_looks.txtr_t[direction]->width / T_SIZE)), data->map_looks.txtr_t[direction]->width);

	tex_y = (top - (D_H / 2) + (size / 2)) * step;
	if (tex_y < 0)
		tex_y = 0;
	
	while (fc < top)
	{
		mlx_put_pixel(data->img, line, fc, data->map_looks.ceiling_c);
		fc++;
	}
	fc = bot;
	while (top < bot)
	{
		pixel_put(data, line, top, get_color(data, direction, (int)tex_x, (int)tex_y));
		top++;
		tex_y += step;
	}
	while (fc < D_H - 1)
	{
		mlx_put_pixel(data->img, line, fc, data->map_looks.floor_c);
		fc++;
	}
}

void	ray_casting(t_data *data)
{
	double dist;
	double x;
	double y;
	int line;
	int	direction_x;
	int direction_y;

	line = 0;
	direction_x = 0;
	direction_y = 0;
	data->plyr->ray_ang = fix_angle(data->plyr->plyr_ang - data->plyr->rad_fov / 2);
	while (line < D_W)
	{
		x = get_inter_x(data, data->plyr->ray_ang, &direction_x);
		y = get_inter_y(data, data->plyr->ray_ang, &direction_y);
		data->plyr->flag = 0;
		if (x <= y)
		{
			dist = x;
			put_lines(data, line, dist, direction_x);
		}
		else
		{
			dist = y;
			data->plyr->flag = 1;
			put_lines(data, line, dist, direction_y);
		}
		line++;
		data->plyr->ray_ang += (data->plyr->rad_fov / D_W);
	}
}

void	loop(void *par)
{
	t_data	*data;

	data = par;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, D_W, D_H);
	if (data->img == NULL)
		error_and_exit(data, "Memory allocation error\n", 42);
	// color(data->img);
	ray_casting(data);
	move(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}