/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 16:37:28 by seyildir      #+#    #+#                 */
/*   Updated: 2024/06/04 21:47:52 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_lines(t_data *data, int line, double dist, int direction)
{
	double	bot;
	double	top;
	double	size;
	
	double	fc;
	double	step;
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
	if (bot > D_H)
		bot = D_H;
	if (bot < D_H / 2)
		bot = D_H / 2 + 1;
	fc = 0;
	step = 1.0 * data->map_looks.txtr_t[direction]->height / size;
	if (data->plyr->flag == 1)
		tex_x = (int)fmodf((data->plyr->horizontal_x * (data->map_looks.txtr_t[direction]->width / T_SIZE)), data->map_looks.txtr_t[direction]->width);
	else
		tex_x = (int)fmodf((data->plyr->vertical_y * (data->map_looks.txtr_t[direction]->width / T_SIZE)), data->map_looks.txtr_t[direction]->width);

	// float hit_point;
	// if (data->plyr->flag == 1)
	// 	hit_point = data->plyr->horizontal_x - floor(data->plyr->horizontal_x);
	// else
	// 	hit_point = data->plyr->vertical_y - floor(data->plyr->vertical_y);
	// tex_x = (int)(hit_point * data->map_looks.txtr_t[direction]->width);
	tex_y = (top - (D_H / 2) + (size / 2)) * step;
	if (tex_y < 0)
		tex_y = 0;
	
	while (fc < top)
	{
		mlx_put_pixel(data->img, line, fc, data->map_looks.ceiling_c);
		fc++;
	}
	fc = bot;
	mlx_put_pixel(data->img, line, top, 0xff0000ff);
	// printf("direction: %d, top: %f, line: %d || tex_y: %d, tex_x: %d\n", direction, top, line, tex_y, tex_x);
	while (top < bot)
	{
		tex_y = tex_y % data->map_looks.txtr_t[direction]->height;
		tex_x = tex_x % data->map_looks.txtr_t[direction]->width;
		color = data->map_looks.txtr_colors[direction][tex_y][tex_x];
		mlx_put_pixel(data->img, line, top, color);
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
	data->plyr->ray_ang = data->plyr->plyr_ang - data->plyr->rad_fov / 2;
	while (line < D_W)
	{
		x = get_inter_x(data, fix_angle(data->plyr->ray_ang), &direction_x);
		y = get_inter_y(data, fix_angle(data->plyr->ray_ang), &direction_y);
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