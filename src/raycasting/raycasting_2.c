/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 16:41:52 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/03 20:26:33 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_inter_x(t_data *data, double angle, int *direction)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	int		x_way;

	x_step = T_SIZE;
	y_step = T_SIZE * tan(angle);
	x = data->plyr->real_x - (data->plyr->real_x % T_SIZE);
	x_way = way_check(angle, &x_step, &x, 'x');
	y = data->plyr->real_y + ((x - data->plyr->real_x) * tan(angle));
	if ((angle_check(angle, 'y') && y_step < 0) || (!angle_check(angle, 'y') && y_step > 0))
		y_step *= -1;
	while (!wall_check(data, x + x_way, y))
	{
		x += x_step;
		y += y_step;
	}
	if (x_step > 0)
		*direction = 3;
	else
		*direction = 2;
	return (sqrt(pow(x - data->plyr->real_x, 2) + pow(y - data->plyr->real_y, 2)));
}

double get_inter_y(t_data *data, double angle, int *direction)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	int		y_way;

	x_step = T_SIZE / tan(angle);
	y_step = T_SIZE;
	y = data->plyr->real_y - (data->plyr->real_y % T_SIZE);
	y_way = way_check(angle, &y_step, &y, 'y');
	x = data->plyr->real_x + ((y - data->plyr->real_y) / tan(angle));
	if ((angle_check(angle, 'x') && x_step > 0) || (!angle_check(angle, 'x') && x_step < 0))
		x_step *= -1;
	while (!wall_check(data, x, y + y_way))
	{
		x += x_step;
		y += y_step;
	}
	if (y_step > 0)
		*direction = 1;
	else
		*direction = 0;
	return (sqrt(pow(x - data->plyr->real_x, 2) + pow(y - data->plyr->real_y, 2)));
}