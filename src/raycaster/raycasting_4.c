/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_4.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/09 18:02:05 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/11 16:58:50 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	pixel_put(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < D_W && y >= 0 && y < D_H)
		mlx_put_pixel(data->img, x, y, color);
}

static uint32_t	get_color(t_data *data, int direction, int x, int y)
{
	if (x < 0)
		x = 0;
	if (x >= (int)data->map_looks.txtr_t[direction]->width)
		x = data->map_looks.txtr_t[direction]->width - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)data->map_looks.txtr_t[direction]->height)
		y = data->map_looks.txtr_t[direction]->height - 1;
	return (data->map_looks.txtr_colors[direction][y][x]);
}

static void	put_lines_while(t_data *data, int line, int direction, double step)
{
	if (data->ray.tex_y < 0)
		data->ray.tex_y = 0;
	while (data->ray.fc < data->ray.top)
	{
		mlx_put_pixel(data->img, line, data->ray.fc, data->map_looks.ceiling_c);
		data->ray.fc++;
	}
	data->ray.fc = data->ray.bot;
	while (data->ray.top < data->ray.bot)
	{
		pixel_put(data, line, data->ray.top, get_color(data, direction, \
		(int)data->ray.tex_x, (int)data->ray.tex_y));
		data->ray.top++;
		data->ray.tex_y += step;
	}
	while (data->ray.fc < D_H - 1)
	{
		mlx_put_pixel(data->img, line, data->ray.fc, data->map_looks.floor_c);
		data->ray.fc++;
	}
	data->ray.fc = 0;
}

static void	put_lines_init_top_bot(t_data *data, double size)
{
	data->ray.top = (D_H / 2) - (size / 2);
	data->ray.bot = (D_H / 2) + (size / 2);
	if (data->ray.top < 0)
		data->ray.top = 0;
	if (data->ray.bot > D_H)
		data->ray.bot = D_H;
	if (data->ray.top > D_H / 2)
		data->ray.top = D_H / 2;
	if (data->ray.bot < 0)
		data->ray.bot = D_H / 2 + 1;
}

void	put_lines(t_data *data, int line, double dist, int direction)
{
	double	size;
	double	step;

	dist *= cos(fix_angle(data->plyr->ray_ang - data->plyr->plyr_ang));
	size = (T_SIZE / dist) * ((D_W / 2) / tan(data->plyr->rad_fov / 2));
	put_lines_init_top_bot(data, size);
	step = (double)data->map_looks.txtr_t[direction]->height / size;
	if (data->plyr->flag == 1)
		data->ray.tex_x = fmod((data->plyr->h_x * \
		((float)data->map_looks.txtr_t[direction]->width / T_SIZE)), \
		data->map_looks.txtr_t[direction]->width);
	else
		data->ray.tex_x = fmod((data->plyr->v_y * \
		((float)data->map_looks.txtr_t[direction]->width / T_SIZE)), \
		data->map_looks.txtr_t[direction]->width);
	data->ray.tex_y = (data->ray.top - (D_H / 2) + (size / 2)) * step;
	put_lines_while(data, line, direction, step);
}
