/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 15:58:47 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/14 16:19:27 by akasiota      ########   odam.nl         */
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

static bool	is_player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' )
		return (true);
	return (false);
}

static void	validate_point(t_data *data, size_t y, size_t x)
{
	if (data->map_coords[y][x] != '0' && data->map_coords[y][x] != '1' \
	&& is_player_pos(data->map_coords[y][x]) == false \
	&& data->map_coords[y][x] != 'V')
		error_and_exit(data, "Unidentified tiles in map\n", 10);
	if (is_player_pos(data->map_coords[y][x]) == true)
	{
		if (data->map_looks.player_pos_parsed == true)
			error_and_exit(data, "Multiple player starting positions\n", 11);
		data->map_looks.player_pos_parsed = true;
	}
}

static bool	valid_suroundings(t_data *data, size_t y, size_t x)
{
	if (y > 0 && (data->map_coords[y - 1][x] == 'V'))
		return (false);
	if (y < data->map_height && (data->map_coords[y + 1][x] == 'V'))
		return (false);
	if (x > 0 && (data->map_coords[y][x - 1] == 'V'))
		return (false);
	if (x < data->map_width && ((data->map_coords[y][x + 1] == 'V') \
	|| (data->map_coords[y][x + 1] == '\0')))
		return (false);
	return (true);
}

static void	validate_enclosure(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		while (data->map_coords[y][x] == '1' || data->map_coords[y][x] == 'V')
		{
			x++;
			while (data->map_coords[y][x] == '0' || is_player_pos(data->map_coords[y][x]) == true)
			{
				// check neighbors
				if (valid_suroundings(data, y, x) == false)
					error_and_exit(data, "Map isn't enclosed by walls\n", 122);
				x++;
			}
		}
		x = 0;
		y++;
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
		while (x < data->map_width && data->map_coords[y][x] != '\0')
		{
			validate_point(data, y, x);
			x++;
		}
		x = 0;
		y++;
	}
	validate_enclosure(data);
}