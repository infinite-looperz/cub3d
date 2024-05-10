/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 16:50:33 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/10 20:35:38 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	data_init(t_data* data)
{
	int	i;

	i = 0;
	data->player = NULL;
	data->mlx = NULL;
	data->map_info = NULL;
	data->map_coords = NULL;
	data->map_height = 0;
	data->map_width = 0;
	// data->map_elements_parsed = false;
	while (i < 4)
	{
		data->map_looks.textures[i] = NULL;
		data->map_looks.direction_parsed[i] = false;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		data->map_looks.floor_color[i] = 0;
		data->map_looks.ceiling_color[i] = 0;
		i++;
	}
	data->map_looks.F_parsed = false;
	data->map_looks.C_parsed = false;
}