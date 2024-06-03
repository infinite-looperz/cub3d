/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 16:37:28 by seyildir      #+#    #+#                 */
/*   Updated: 2024/06/03 20:32:45 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_lines(t_data *data, int line, double dist, int direction)
{
	double	bot;
	double	top;
	double	size;
	
	double	fc;
	int		line_height;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		tex_x;
	int		color;
	

	dist *= cos(fix_angle(data->plyr->ray_ang - data->plyr->plyr_ang));
	size = (T_SIZE / dist) * ((D_W / 2) / tan(data->plyr->rad_fov / 2));
	top = (D_H / 2) - (size / 2);
	bot = (D_H / 2) + (size / 2);
	if (top < 0)
		top = 0;
	if (top > D_H / 2)
		top = D_H / 2;
	if (bot >= D_H)
		bot = D_H - 1;
	if (bot < D_H / 2)
		bot = D_H / 2 + 1;
	fc = 0;
	line_height = bot - top;
	step = 1.0 * TEX_H / line_height;
	// step = TEX_H / size;
	tex_pos = (top - D_H / 2 + line_height / 2) * step;
	
	while (fc < top)
	{
		mlx_put_pixel(data->img, line, fc, 0xAff0fff);
		fc++;
	}
	fc = bot;
	mlx_put_pixel(data->img, line, top, 0xff0000ff);
	while (top < bot)
	{
		// printf("%x\n", data->map_looks.txtr_colors[0][0][0]);
		tex_y = ((int)(tex_pos)) & (TEX_H - 1);
		tex_x = line & (TEX_W - 1);
		// printf("tex_y: %d, line: %d\n", tex_y, line);
		color = data->map_looks.txtr_colors[direction][tex_y][tex_x];
		mlx_put_pixel(data->img, line, top, color);
		top++;
		tex_pos += step;
	}
	mlx_put_pixel(data->img, line, bot, 0xff0000ff);
	while (fc < D_H - 1)
	{
		mlx_put_pixel(data->img, line, fc, 0xAf00AAff);
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
	data->plyr->ray_ang = data->plyr->plyr_ang - data->plyr->rad_fov / 2;
	while (line < D_W)
	{
		x = get_inter_x(data, fix_angle(data->plyr->ray_ang), &direction_x);
		y = get_inter_y(data, fix_angle(data->plyr->ray_ang), &direction_y);
		data->plyr->flag = 0;
		if (x < y)
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
		data->plyr->ray_ang += data->plyr->rad_fov / D_W;
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