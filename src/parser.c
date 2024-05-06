/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 16:59:34 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/06 15:14:06 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	validate_args(int arg_count, char** args)
{
	int	map_name_len;
	int	i;

	if (arg_count != 2)
	{
		// make an exit error function that frees allocated stuff, throws an error and exits
		ft_printf("Usage: ./cub3d [filename]\n");
		exit(1);
	}
	map_name_len = ft_strlen(args[1]);
	i = 0;
	if (map_name_len > 4)
	{
		while ((map_name_len - i) > 4)
			i++;
		if (ft_strncmp(&args[1][i], ".cub", 4) != 0)
		{
			// make an exit error function that frees allocated stuff, throws an error and exits
			ft_printf("Filename extension needs to be .cub\n");
			exit(1);
		}
	}
	else
		exit(1);
		// error
	
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
		tmp = ft_split(data->map_info[i], ' ');
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
			{
				printf("Wrong element identifier for wall textures\n");
				exit(1);
			}
			free(tmp[0]);
			free(tmp);
			tmp = NULL;
		}
		else if (ft_strlen(tmp[0]) == 1)
		{
			tmp_2 = ft_split(tmp[1], ',');
			if (ft_strncmp(tmp[0], "F", 2) == 0)
			{
				data->map_looks.floor_color[RED] = ft_atoi(tmp_2[RED]);
				data->map_looks.floor_color[GREEN] = ft_atoi(tmp_2[GREEN]);
				data->map_looks.floor_color[BLUE] = ft_atoi(tmp_2[BLUE]);		
			}
			else if (ft_strncmp(tmp[0], "C", 2) == 0)
			{
				data->map_looks.ceiling_color[RED] = ft_atoi(tmp_2[RED]);
				data->map_looks.ceiling_color[GREEN] = ft_atoi(tmp_2[GREEN]);
				data->map_looks.ceiling_color[BLUE] = ft_atoi(tmp_2[BLUE]);		
			}
			else
			{
				printf("Wrong element identifier for floor and/or ceiling colors\n");
				exit(1);
			}
			// Free tmp_2
			free_2D_array((void**)tmp_2);
			free_2D_array((void**)tmp);
		}
		else if (ft_strlen(tmp[0]) >= 3)
		{
			printf("Probably the map");
		}
		else
		{
			printf("Wrong element identifier or the map is not the last element\n");
			exit(1);
		}
		i++;
	}
}

void	print_stored_info(t_data *data)
{
	int i;
	
	i = 0;
	while (data->map_info[i] != NULL)
	{
		ft_printf("%s", data->map_info[i]);
		i++;
	}
	i = 0;
	while (data->map_looks.textures[i] != NULL && i < 4)
	{
		printf("%s\n", data->map_looks.textures[i]);
		i++;
	}
}

void	validate_map(t_data *data, char* filename)
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
			printf("Need more pointers for the lines\n");
		}
	}
	store_textures_and_colors(data);
	// Test what is stored
	print_stored_info(data);
}