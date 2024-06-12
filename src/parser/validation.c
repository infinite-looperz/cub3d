/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 15:58:47 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/12 17:54:03 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static bool	is_player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' )
		return (true);
	return (false);
}

static void	validate_point(t_data *data, size_t y, size_t x)
{
	if (data->map_c[y][x] != '0' && data->map_c[y][x] != '1' \
	&& is_player_pos(data->map_c[y][x]) == false \
	&& data->map_c[y][x] != 'V')
		error_and_exit(data, "Unidentified tiles in map\n", 10);
	if (is_player_pos(data->map_c[y][x]) == true)
	{
		if (data->map_looks.player_pos_parsed == true)
			error_and_exit(data, "Multiple player starting positions\n", 11);
		data->map_looks.player_pos_parsed = true;
	}
}

static void	validate_enclosure(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while (y < data->map_h)
	{
		while (data->map_c[y][x] != '\0')
		{
			while (data->map_c[y][x] == '0' \
			|| is_player_pos(data->map_c[y][x]) == true)
			{
				if (valid_suroundings(data, y, x) == false)
					error_and_exit(data, "Map isn't enclosed by walls\n", 122);
				x++;
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (data->map_looks.player_pos_parsed == false)
		error_and_exit(data, "Missing player starting position\n", 12);
}

void	validate_map(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while (y < data->map_h)
	{
		while (x < data->map_w && data->map_c[y][x] != '\0')
		{
			validate_point(data, y, x);
			x++;
		}
		x = 0;
		y++;
	}
	validate_enclosure(data);
}
