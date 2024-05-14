/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 15:58:47 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/10 21:14:10 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	validate_args(t_data* data, int arg_count, char** args)
{
	int	map_name_len;
	int	i;

	if (arg_count != 2)
		error_and_exit(data, "Usage: ./cub3d [filename]\n", 1);
	map_name_len = ft_strlen(args[1]);
	i = 0;
	if (map_name_len > 4)
	{
		while ((map_name_len - i) > 4)
			i++;
		if (ft_strncmp(&args[1][i], ".cub", 4) != 0)
			error_and_exit(data, "Filename extension needs to be .cub\n", 2);
	}
	else
		error_and_exit(data, "Filename needs extension .cub\n", 3);
	return ;
}

static void	validate_point(t_data *data, size_t y, size_t x)
{
	if (data->map_coords[y][x] != '0' && data->map_coords[y][x] != '1' \
	&& data->map_coords[y][x] != 'N' && data->map_coords[y][x] != 'S' \
	&& data->map_coords[y][x] != 'W' && data->map_coords[y][x] != 'E')
		error_and_exit(data, "Unidentified tiles in map\n", 10);
}

static void	validate_enclosure(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		if (data->map_coords[y][0] != '1' || data->map_coords[y][data->map_width - 1] != '1')
			error_and_exit(data, "Map isn't enclosed by walls\n", 122);
		y++;
	}
	while (x < data->map_width)
	{
		if (data->map_coords[0][x] != '1' || data->map_coords[data->map_height - 1][x] != '1')
			error_and_exit(data, "Map isn't enclosed by walls\n", 122);
		x++;
	}
}

void	validate_map(t_data *data)
{
	size_t	y;
	size_t	x;
	

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			validate_point(data, y, x);
			x++;
		}
		x = 0;
		y++;
	}
	validate_enclosure(data);
}