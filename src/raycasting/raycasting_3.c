/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_3.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 16:43:23 by seyildir      #+#    #+#                 */
/*   Updated: 2024/06/03 20:33:01 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fix_angle(double angle)
{
	if (angle < 0)
		angle = fmod(angle, 2 * M_PI) + 2 * M_PI;
	else if (angle > (2 * M_PI))
		angle = fmod(angle, 2 * M_PI);
	return (angle);
}

int	way_check(double angle, double *step, double *way, char x_y)
{
	if((x_y == 'x' && (angle < M_PI / 2 || angle > 3 * M_PI / 2))
		|| (x_y == 'y' && (angle > 0 && angle < M_PI)))
	{
		*way += T_SIZE;
		return (1);
	}
	*step *= -1;
	return (-1);
}

bool	angle_check(double angle, char c)
{
	if ((c == 'x' && (angle > M_PI / 2 && angle < 3 * M_PI / 2))
		|| (c == 'y' && (angle > 0 && angle < M_PI)))
		return (true);
	return (false);
}

bool	wall_check(t_data *data, double x, double y)
{
	size_t	x_map;
	size_t	y_map;

	if (x < 0 || y < 0)
		return (true);
	x_map = x / T_SIZE;
	y_map = y / T_SIZE;
	if (y_map >= data->map_h || x_map >= data->map_w)
		return (true);
	if (data->map_c[y_map] && x_map <= ft_strlen(data->map_c[y_map]))
		if (data->map_c[y_map][x_map] == '1')
			return (true);
	return (false);
}
