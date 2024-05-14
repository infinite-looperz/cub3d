/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 16:59:34 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/14 17:47:02 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	map_dimensions(t_data *data, size_t i)
{
	size_t	line_len;
	
	while (data->map_info[i] != NULL)
	{
		data->map_height++;
		line_len = ft_strlen(data->map_info[i]);
		if (line_len > data->map_width)
			data->map_width = line_len;
		i++;
	}
}

static void	store_coordinates(t_data *data, size_t i)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	map_dimensions(data, i);
	data->map_coords = ft_calloc_cub3d(data, data->map_height + 1, sizeof(char *));
	while (y < data->map_height && data->map_info[i] != NULL)
	{
		if (data->map_info[i][x] == '\n')
			error_and_exit(data, "Map contains an empty line\n", 9);
		data->map_coords[y] = ft_calloc_cub3d(data, data->map_width + 1, sizeof(char));
		while (x < data->map_width && data->map_info[i][x] != '\0')
		{
			if (data->map_info[i][x] != '\n' && data->map_info[i][x] != ' ')
				data->map_coords[y][x] = data->map_info[i][x];
			else
				data->map_coords[y][x] = 'V';
			x++;
		}
		x = 0;
		y++;
		i++;
	}
}

static void	store_texture(t_data *data, t_direction direction, char **tmp, size_t i)
{
	tmp = ft_split_cub3d(data, data->map_info[i]);
	data->map_looks.textures[direction] = tmp[1];
	data->map_looks.direction_parsed[direction] = true;
	free_and_null((void**)&tmp[0]);
	free(tmp);
	tmp = NULL;
}

static void	validate_colors(t_data *data)
{
	size_t	i;

	i = 0;
	while ( i < 3)
	{
		if (data->map_looks.floor_color[i] < 0 || data->map_looks.floor_color[i] > 255)
			error_and_exit(data, "Color values out of range\n", 85);
		if (data->map_looks.ceiling_color[i] < 0 || data->map_looks.ceiling_color[i] > 255)
			error_and_exit(data, "Color values out of range\n", 85);
		i++;
	}
}

static void	store_map_info(t_data *data)
{
	char**	tmp;
	char**	tmp_2;
	size_t	i;
	
	i = 0;
	tmp = NULL;
	tmp_2 = NULL;
	while (data->map_info != NULL && data->map_info[i] != NULL)
	{
		if (data->map_info[i][0] == '\n')
			i++;
		else
		{
			if (ft_strncmp(data->map_info[i], "NO ", 3) == 0 && data->map_looks.direction_parsed[NORTH] == false)
				store_texture(data, NORTH, tmp, i);
			else if (ft_strncmp(data->map_info[i], "SO ", 3) == 0 && data->map_looks.direction_parsed[SOUTH] == false)
				store_texture(data, SOUTH, tmp, i);
			else if (ft_strncmp(data->map_info[i], "WE ", 3) == 0 && data->map_looks.direction_parsed[WEST] == false)
				store_texture(data, WEST, tmp, i);
			else if (ft_strncmp(data->map_info[i], "EA ", 3) == 0 && data->map_looks.direction_parsed[EAST] == false)
				store_texture(data, EAST, tmp, i);
			else if (ft_strncmp(data->map_info[i], "F ", 2) == 0 && data->map_looks.F_parsed == false)
			{
				tmp = ft_split_cub3d(data, data->map_info[i]);
				tmp_2 = ft_split(tmp[1], ',');
				data->map_looks.floor_color[RED] = ft_atoi_cub3d(data, tmp_2[RED], tmp, tmp_2);
				data->map_looks.floor_color[GREEN] = ft_atoi_cub3d(data, tmp_2[GREEN], tmp, tmp_2);
				data->map_looks.floor_color[BLUE] = ft_atoi_cub3d(data, tmp_2[BLUE], tmp, tmp_2);
				data->map_looks.F_parsed = true;
				free_2d_array((void**)tmp);
				free_2d_array((void**)tmp_2);
			}
			else if (ft_strncmp(data->map_info[i], "C ", 2) == 0 && data->map_looks.C_parsed == false)
			{
				tmp = ft_split_cub3d(data, data->map_info[i]);
				tmp_2 = ft_split(tmp[1], ',');
				data->map_looks.ceiling_color[RED] = ft_atoi_cub3d(data, tmp_2[RED], tmp, tmp_2);
				data->map_looks.ceiling_color[GREEN] = ft_atoi_cub3d(data, tmp_2[GREEN], tmp, tmp_2);
				data->map_looks.ceiling_color[BLUE] = ft_atoi_cub3d(data, tmp_2[BLUE], tmp, tmp_2);
				data->map_looks.C_parsed = true;
				free_2d_array((void**)tmp);
				free_2d_array((void**)tmp_2);
			}
			else if ((data->map_info[i][0] == ' ' || data->map_info[i][0] == '1') && check_parsing_stage(data) == true)
			{
				store_coordinates(data, i);
				break ;
			}
			else
			{
				free_2d_array((void**)tmp);
				error_and_exit(data, "Wrong element identifier or the map is not the last element\n", 6);
			}
			i++;
		}
		
	}
}

static void	print_stored_info(t_data *data)
{
	size_t i;
	
	i = 0;
	printf("\n-----------Map info-----------\n");
	while (data->map_info[i] != NULL)
	{
		ft_printf("%s", data->map_info[i]);
		i++;
	}
	i = 0;
	printf("\n-----------Texture files-----------\n");
	while (data->map_looks.textures[i] != NULL && i < 4)
	{
		printf("%s\n", data->map_looks.textures[i]);
		i++;
	}
	i = 0;
	printf("\n-----------Colors-----------\n");
	while (i < 3)
	{
		printf("floor: %d\n", data->map_looks.floor_color[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("ceiling: %d\n", data->map_looks.ceiling_color[i]);
		i++;
	}
	i = 0;
	printf("\n-----------Map-----------\n");
	while (i < data->map_height)
	{
		printf("%lu:	%s\n", i, data->map_coords[i]);
		i++;
	}
}

void	open_and_store(t_data* data, char* filename)
{
	int		fd;
	size_t	i;

	i = 0;
	data->map_info = ft_calloc_cub3d(data, 10000 + 1, sizeof(char *));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_and_exit(data, "Error opening the map file\n", 8);
	data->map_info[i] = get_next_line(fd);
	while (data->map_info[i] != NULL && i < 10000)
	{
		i++;
		data->map_info[i] = get_next_line(fd);
		if (data->map_info[i] != NULL && i >= 10000)
		{
			// reallocate memory
			error_and_exit(data, "Need more memory for the map\n", 0);
		}
	}
	store_map_info(data);
	validate_colors(data);
	// Test what is stored
	print_stored_info(data);
}
