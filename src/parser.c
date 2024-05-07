/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 16:59:34 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/07 20:04:19 by akasiota      ########   odam.nl         */
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

void	store_textures_and_colors(t_data *data)
{
	char**	tmp;
	char**	tmp_2;
	int		i;
	
	i = 0;
	tmp_2 = NULL;
	while (data->map_info != NULL && data->map_info[i] != NULL)
	{
		tmp = ft_split_cub3d(data, data->map_info[i]);
		if (tmp == NULL)
			error_and_exit(data, "Malloc error", 42);
		if (ft_strlen(tmp[0]) == 2)
		{
			if (ft_strncmp(tmp[0], "NO", 3) == 0)
				data->map_looks.textures[NORTH] = tmp[1];
			else if (ft_strncmp(tmp[0], "SO", 3) == 0)
				data->map_looks.textures[SOUTH] = tmp[1];
			else if (ft_strncmp(tmp[0], "WE", 3) == 0)
				data->map_looks.textures[WEST] = tmp[1];
			else if (ft_strncmp(tmp[0], "EA", 3) == 0)
				data->map_looks.textures[EAST] = tmp[1];
			else
				error_and_exit(data, "Wrong element identifier for wall textures\n", 4);
			free(tmp[0]);
			free(tmp);
			tmp = NULL;
		}
		else if (ft_strlen(tmp[0]) == 1)
		{
			tmp_2 = ft_split(tmp[1], ',');
			if (ft_strncmp(tmp[0], "F", 2) == 0)
			{
				data->map_looks.floor_color[RED] = ft_atoi_cub3d(data, tmp_2[RED], tmp, tmp_2);
				data->map_looks.floor_color[GREEN] = ft_atoi_cub3d(data, tmp_2[GREEN], tmp, tmp_2);
				data->map_looks.floor_color[BLUE] = ft_atoi_cub3d(data, tmp_2[BLUE], tmp, tmp_2);		
			}
			else if (ft_strncmp(tmp[0], "C", 2) == 0)
			{
				data->map_looks.ceiling_color[RED] = ft_atoi_cub3d(data, tmp_2[RED], tmp, tmp_2);
				data->map_looks.ceiling_color[GREEN] = ft_atoi_cub3d(data, tmp_2[GREEN], tmp, tmp_2);
				data->map_looks.ceiling_color[BLUE] = ft_atoi_cub3d(data, tmp_2[BLUE], tmp, tmp_2);		
			}
			else
			{
				free_2D_array((void**)tmp_2);
				free_2D_array((void**)tmp);
				error_and_exit(data, "Wrong element identifier for floor and/or ceiling colors\n", 5);
			}
			free_2D_array((void**)tmp_2);
			free_2D_array((void**)tmp);
		}
		else if (ft_strlen(tmp[0]) >= 3)
		{
			printf("Probably the map");
		}
		else
			error_and_exit(data, "Wrong element identifier or the map is not the last element\n", 6);
		i++;
	}
}

void	print_stored_info(t_data *data)
{
	int i;
	
	i = 0;
	printf("-----------Map info-----------\n");
	while (data->map_info[i] != NULL)
	{
		ft_printf("%s", data->map_info[i]);
		i++;
	}
	i = 0;
	printf("-----------Texture files-----------\n");
	while (data->map_looks.textures[i] != NULL && i < 4)
	{
		printf("%s\n", data->map_looks.textures[i]);
		i++;
	}
	i = 0;
	printf("-----------Colors-----------\n");
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
}

void	validate_map(t_data* data, char* filename)
{
	int		fd;
	// char*	line;
	int		i;

	i = 0;
	data->map_info = ft_calloc(10000 + 1, sizeof(char*));
	if (data->map_info == NULL)
		exit(1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
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
	store_textures_and_colors(data);
	// Test what is stored
	print_stored_info(data);
}