/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 16:54:50 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/12 18:11:00 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static size_t	get_len_to_end_wall(t_data *data, size_t y)
{
	size_t	i;

	i = 0;
	while (i < data->map_w)
	{
		if (data->map_c[y][i + 1] == 'V' || data->map_c[y][i + 1] == '\0')
			break ;
		i++;
	}
	while (data->map_c[y][i] == '1' && i > 0)
	{
		i--;
	}
	return (i + 2);
}

static size_t	get_len_to_start_wall(t_data *data, size_t y)
{
	size_t	i;

	i = 0;
	while (i < data->map_w)
	{
		if (data->map_c[y][i] == 'V' || data->map_c[y][i] == '1')
			i++;
		else
			break ;
	}
	return (i);
}

static bool	valid_start_outer_corners(t_data *data, size_t x, size_t y)
{
	size_t	len_to_start;

	len_to_start = get_len_to_start_wall(data, y);
	if ((data->map_w > 1 && x == len_to_start) && (data->map_h > 1 && y >= 1))
	{
		if (data->map_c[y][x - 1] == 'V' || data->map_c[y - 1][x - 1] == 'V')
			return (false);
	}
	if ((data->map_w > 1 && x == len_to_start) \
	&& (data->map_h > 1 && y <= data->map_h - 1))
	{
		if (data->map_c[y][x - 1] == 'V' || data->map_c[y + 1][x - 1] == 'V')
			return (false);
	}
	return (true);
}

static bool	valid_outer_corners(t_data *data, size_t x, size_t y)
{
	size_t	len_to_end;

	len_to_end = get_len_to_end_wall(data, y);
	if ((data->map_w > 1 && x == len_to_end - 2) && (data->map_h > 1 && y >= 1))
	{
		if (data->map_c[y][x + 1] == 'V' || data->map_c[y - 1][x + 1] == 'V')
			return (false);
	}
	if ((data->map_w > 1 && x == len_to_end - 2) \
	&& (data->map_h > 1 && y <= data->map_h - 1))
	{
		if (data->map_c[y][x + 1] == 'V' || data->map_c[y + 1][x + 1] == 'V' \
		||data->map_c[y + 1][x + 1] == '\0')
			return (false);
	}
	return (valid_start_outer_corners(data, x, y));
}

bool	valid_suroundings(t_data *data, size_t y, size_t x)
{
	if (y == 0 || x == 0)
		return (false);
	if (y > 0 && x > 1 && x < data->map_w && (data->map_c[y - 1][x] == 'V' \
	|| data->map_c[y - 1][x - 1] == 'V' || data->map_c[y - 1][x + 1] == 'V'))
		return (false);
	if (y < data->map_h && x > 1 && x < data->map_w \
	&& (data->map_c[y + 1][x] == 'V' \
	|| data->map_c[y + 1][x] == '\0' || data->map_c[y + 1][x - 1] == 'V' \
	|| data->map_c[y + 1][x - 1] == '\0' || data->map_c[y + 1][x + 1] == 'V' \
	|| data->map_c[y + 1][x + 1] == '\0'))
		return (false);
	if (x > 0 && (data->map_c[y][x - 1] == 'V'))
		return (false);
	if (x < data->map_w && ((data->map_c[y][x + 1] == 'V') \
	|| (data->map_c[y][x + 1] == '\0')))
		return (false);
	return (valid_outer_corners(data, x, y));
}
