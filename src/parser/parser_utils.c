/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 19:03:29 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/09 18:11:21 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static bool	parse_textures(t_data *data, char **tmp, size_t	i)
{
	if (ft_strncmp(data->map_i[i], "NO ", 3) == 0 \
	&& data->map_looks.direction_parsed[NORTH] == false)
		get_txtr(data, NORTH, tmp, i);
	else if (ft_strncmp(data->map_i[i], "SO ", 3) == 0 \
	&& data->map_looks.direction_parsed[SOUTH] == false)
		get_txtr(data, SOUTH, tmp, i);
	else if (ft_strncmp(data->map_i[i], "WE ", 3) == 0 \
	&& data->map_looks.direction_parsed[WEST] == false)
		get_txtr(data, WEST, tmp, i);
	else if (ft_strncmp(data->map_i[i], "EA ", 3) == 0 \
	&& data->map_looks.direction_parsed[EAST] == false)
		get_txtr(data, EAST, tmp, i);
	else
		return (false);
	return (true);
}

static bool	parse_f_colors(t_data *data, char **tmp, size_t i)
{
	char	**tmp_2;

	tmp_2 = NULL;
	if (ft_strncmp(data->map_i[i], "F ", 2) == 0 \
	&& data->map_looks.f_parsed == false)
	{
		tmp = ft_split_cub3d(data, data->map_i[i]);
		tmp_2 = ft_split(tmp[1], ',');
		data->map_looks.floor_c = \
		cub3d_atoi(data, tmp_2[RED], tmp, tmp_2) << 24 \
		| cub3d_atoi(data, tmp_2[GREEN], tmp, tmp_2) << 16 \
		| cub3d_atoi(data, tmp_2[BLUE], tmp, tmp_2) << 8 | 0xFF;
		data->map_looks.f_parsed = true;
		free_2d_array((void **)tmp);
		free_2d_array((void **)tmp_2);
	}
	else
		return (false);
	return (true);
}

static bool	parse_c_colors(t_data *data, char **tmp, size_t i)
{
	char	**tmp_2;

	tmp_2 = NULL;
	if (ft_strncmp(data->map_i[i], "C ", 2) == 0 \
	&& data->map_looks.c_parsed == false)
	{
		tmp = ft_split_cub3d(data, data->map_i[i]);
		tmp_2 = ft_split(tmp[1], ',');
		data->map_looks.ceiling_c = \
		cub3d_atoi(data, tmp_2[RED], tmp, tmp_2) << 24 \
		| cub3d_atoi(data, tmp_2[GREEN], tmp, tmp_2) << 16 \
		| cub3d_atoi(data, tmp_2[BLUE], tmp, tmp_2) << 8 | 0xFF;
		data->map_looks.c_parsed = true;
		free_2d_array((void **)tmp);
		free_2d_array((void **)tmp_2);
	}
	else
		return (false);
	return (true);
}

static bool	parse_coordinates(t_data *data, size_t i)
{
	if ((data->map_i[i][0] == ' ' || data->map_i[i][0] == '1') \
	&& check_parsing_stage(data) == true)
		store_coordinates(data, i);
	else
		return (false);
	return (true);
}

void	store_map_info(t_data *data)
{
	char	**tmp;
	size_t	i;

	i = 0;
	tmp = NULL;
	while (data->map_i != NULL && data->map_i[i] != NULL)
	{
		if (data->map_i[i][0] == '\n')
			;
		else if (parse_textures(data, tmp, i) == true)
			;
		else if (parse_f_colors(data, tmp, i) == true)
			;
		else if (parse_c_colors(data, tmp, i) == true)
			;
		else if (parse_coordinates(data, i) == true)
			break ;
		else
		{
			free_2d_array((void **)tmp);
			error_and_exit(data, "Wrong element identifier \
or the map is not the last element\n", 6);
		}
		i++;
	}
}
