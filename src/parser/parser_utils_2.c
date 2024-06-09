/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 16:59:34 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/09 20:10:11 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	map_dimensions(t_data *data, size_t i)
{
	size_t	line_len;

	while (data->map_i[i] != NULL)
	{
		data->map_h++;
		line_len = ft_strlen(data->map_i[i]);
		if (line_len > data->map_w)
			data->map_w = line_len;
		i++;
	}
}

static void	tile_assignment(t_data *data, size_t i, size_t y, size_t x)
{
	if (data->map_i[i][x] != '\n' && data->map_i[i][x] != ' ')
	{
		if (data->map_i[i][x] != '1' && data->map_i[i][x] != '0' \
		&& data->map_i[i][x] != 'N' && data->map_i[i][x] != 'S' \
		&& data->map_i[i][x] != 'W' && data->map_i[i][x] != 'E')
			error_and_exit(data, "Unidentified tiles in map\n", 10);
		data->map_c[y][x] = data->map_i[i][x];
	}
	else
		data->map_c[y][x] = 'V';
}

void	store_coordinates(t_data *data, size_t i)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	map_dimensions(data, i);
	data->map_c = ft_calloc_cub3d(data, data->map_h + 1, sizeof(char *));
	while (y < data->map_h && data->map_i[i] != NULL)
	{
		if (data->map_i[i][x] == '\n')
			error_and_exit(data, "Map contains an empty line\n", 9);
		data->map_c[y] = ft_calloc_cub3d(data, data->map_w + 1, sizeof(char));
		while (x < data->map_w && data->map_i[i][x] != '\0')
		{
			tile_assignment(data, i, y, x);
			x++;
		}
		x = 0;
		y++;
		i++;
	}
}

static void	get_txtr_colors(t_data *data, t_direction direction)
{
	size_t	y;
	size_t	i;
	size_t	x;

	y = 0;
	i = 0;
	x = 0;
	while (y < data->map_looks.txtr_t[direction]->height)
	{
		data->map_looks.txtr_colors[direction][y] = ft_calloc_cub3d(data, \
		data->map_looks.txtr_t[direction]->width + 1, sizeof(int));
		while (x < data->map_looks.txtr_t[direction]->width)
		{
			data->map_looks.txtr_colors[direction][y][x] = \
			(data->map_looks.txtr_t[direction]->pixels[i] << 24 \
			| data->map_looks.txtr_t[direction]->pixels[i + 1] << 16 \
			| data->map_looks.txtr_t[direction]->pixels[i + 2] << 8 \
			| data->map_looks.txtr_t[direction]->pixels[i + 3]);
			i += 4;
			x++;
		}
		x = 0;
		y++;
	}
}

void	get_txtr(t_data *data, t_direction direction, char **tmp, size_t i)
{
	tmp = ft_split_cub3d(data, data->map_i[i]);
	data->map_looks.textures[direction] = tmp[1];
	data->map_looks.txtr_t[direction] = mlx_load_png(tmp[1]);
	if (data->map_looks.txtr_t[direction] == NULL)
		error_and_exit(data, "Error loading textures\n", 52);
	data->map_looks.txtr_colors[direction] = ft_calloc_cub3d(data, \
	data->map_looks.txtr_t[direction]->height + 1, sizeof(int *));
	get_txtr_colors(data, direction);
	data->map_looks.direction_parsed[direction] = true;
	free_and_null((void **)&tmp[0]);
	free(tmp);
}
