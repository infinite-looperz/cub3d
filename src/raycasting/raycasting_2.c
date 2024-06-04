/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 16:41:52 by seyildir      #+#    #+#                 */
/*   Updated: 2024/06/04 21:56:52 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_inter_x(t_data *data, double angle, int *direction)
{
	double	x_step;
	double	y_step;
	int		x_way;

	x_step = T_SIZE;
	y_step = T_SIZE * tan(angle);
	data->plyr->vertical_x = data->plyr->real_x - (data->plyr->real_x % T_SIZE);
	x_way = way_check(angle, &x_step, &data->plyr->vertical_x, 'x');
	data->plyr->vertical_y = data->plyr->real_y + ((data->plyr->vertical_x - data->plyr->real_x) * tan(angle));
	if ((angle_check(angle, 'y') && y_step < 0) || (!angle_check(angle, 'y') && y_step > 0))
		y_step *= -1;
	while (!wall_check(data, data->plyr->vertical_x + x_way, data->plyr->vertical_y))
	{
		data->plyr->vertical_x += x_step;
		data->plyr->vertical_y += y_step;
	}
	if (x_step > 0)
		*direction = 2;
	else
		*direction = 3;
	return (sqrt(pow(data->plyr->vertical_x - data->plyr->real_x, 2) + pow(data->plyr->vertical_y - data->plyr->real_y, 2)));
}

double get_inter_y(t_data *data, double angle, int *direction)
{
	double	x_step;
	double	y_step;
	int		y_way;

	x_step = T_SIZE / tan(angle);
	y_step = T_SIZE;
	data->plyr->horizontal_y = data->plyr->real_y - (data->plyr->real_y % T_SIZE);
	y_way = way_check(angle, &y_step, &data->plyr->horizontal_y, 'y');
	data->plyr->horizontal_x = data->plyr->real_x + ((data->plyr->horizontal_y - data->plyr->real_y) / tan(angle));
	if ((angle_check(angle, 'x') && x_step > 0) || (!angle_check(angle, 'x') && x_step < 0))
		x_step *= -1;
	while (!wall_check(data, data->plyr->horizontal_x, data->plyr->horizontal_y + y_way))
	{
		data->plyr->horizontal_x += x_step;
		data->plyr->horizontal_y += y_step;
	}
	if (y_step > 0)
		*direction = 1;
	else
		*direction = 0;
	return (sqrt(pow(data->plyr->horizontal_x - data->plyr->real_x, 2) + pow(data->plyr->horizontal_y - data->plyr->real_y, 2)));
}