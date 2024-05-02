/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/02 16:59:34 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/02 18:53:19 by akasiota      ########   odam.nl         */
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
	}
	i = 0;
	while (data->map_info[i] != NULL)
	{
		ft_printf("%s", data->map_info[i]);
		i++;
	}
}