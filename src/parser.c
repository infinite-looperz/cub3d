/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 18:19:53 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/14 20:53:51 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// static void	get_map_info_lines(t_data *data, char *filename)
// {
// 	char*	line;
// 	int		fd;
// 	size_t	i;

// 	line = NULL;
// 	i = 0;
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		error_and_exit(data, "Error opening the map file\n", 8);
// 	line = 
	
// }

void	open_and_store(t_data *data, char *filename)
{
	int		fd;
	size_t	i;

	i = 0;
	data->map_i = ft_calloc_cub3d(data, 10000 + 1, sizeof(char *));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_and_exit(data, "Error opening the map file\n", 8);
	data->map_i[i] = get_next_line(fd);
	while (data->map_i[i] != NULL && i < 10000)
	{
		i++;
		data->map_i[i] = get_next_line(fd);
		if (data->map_i[i] != NULL && i >= 10000)
		{
			// reallocate memory - remove comment when fixed
			error_and_exit(data, "Need more memory for the map\n", 0);
		}
	}
	store_map_info(data);
	validate_colors(data);
	// Test what is stored - delete afterwards
	print_stored_info(data);
}
