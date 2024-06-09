/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 18:19:53 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/09 18:11:29 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_parsing_stage(t_data *data)
{
	if (data->map_looks.direction_parsed[NORTH] == true \
	&& data->map_looks.direction_parsed[SOUTH] == true \
	&& data->map_looks.direction_parsed[WEST] == true \
	&& data->map_looks.direction_parsed[EAST] == true \
	&& data->map_looks.f_parsed == true && data->map_looks.c_parsed == true)
		return (true);
	return (false);
}

static size_t	get_map_info_lines(t_data *data, char *filename)
{
	char	*line;
	int		fd;
	size_t	i;

	line = NULL;
	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_and_exit(data, "Error opening the map file\n", 8);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

static void	player_orientation(t_data *data, char c)
{
	if (c == 'E')
		data->plyr->plyr_ang = 0;
	if (c == 'S')
		data->plyr->plyr_ang = M_PI / 2;
	if (c == 'W')
		data->plyr->plyr_ang = M_PI;
	if (c == 'N')
		data->plyr->plyr_ang = 3 * M_PI / 2;
}

static void	player_position(t_data *data)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	data->plyr = ft_calloc_cub3d(data, 1, sizeof(t_player));
	while (y < data->map_h)
	{
		while (x < data->map_w)
		{
			if (data->map_c[y][x] == 'N' || data->map_c[y][x] == 'S' \
			|| data->map_c[y][x] == 'E' || data->map_c[y][x] == 'W')
			{
				data->plyr->x = x;
				data->plyr->y = y;
				player_orientation(data, data->map_c[y][x]);
				break ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	open_and_store(t_data *data, char *filename)
{
	int		fd;
	size_t	i;

	i = 0;
	data->map_i = ft_calloc_cub3d(data, \
	get_map_info_lines(data, filename) + 1, sizeof(char *));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_and_exit(data, "Error opening the map file\n", 8);
	data->map_i[i] = get_next_line(fd);
	while (data->map_i[i] != NULL)
	{
		i++;
		data->map_i[i] = get_next_line(fd);
		printf("%s", data->map_i[i]);
	}
	close(fd);
	store_map_info(data);
	player_position(data);
}
