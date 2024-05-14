/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 16:50:33 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/14 17:52:41 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	initialize_texture_array(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->map_looks.textures[i] = NULL;
		data->map_looks.direction_parsed[i] = false;
		i++;
	}
}

static void	initialize_colors_arrays(t_data *data)
{
	int	i;

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

void	data_init(t_data *data)
{
	data->player = NULL;
	data->mlx = NULL;
	data->map_info = NULL;
	data->map_coords = NULL;
	data->map_height = 0;
	data->map_width = 0;
	initialize_texture_array(data);
	initialize_colors_arrays(data);
	data->map_looks.player_pos_parsed = false;
}
