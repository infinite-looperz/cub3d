/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 16:50:33 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/04 19:51:12 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	initialize_texture_arrays(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->map_looks.textures[i] = NULL;
		data->map_looks.txtr_t[i] = NULL;
		data->map_looks.txtr_colors[i] = NULL;
		data->map_looks.direction_parsed[i] = false;
		i++;
	}
}

static void	initialize_colors_arrays(t_data *data)
{
	data->map_looks.floor_c = 0;
	data->map_looks.ceiling_c = 0;
	data->map_looks.f_parsed = false;
	data->map_looks.c_parsed = false;
}

void	data_init(t_data *data)
{
	data->plyr = NULL;
	data->mlx = NULL;
	data->map_i = NULL;
	data->map_c = NULL;
	data->map_h = 0;
	data->map_w = 0;
	initialize_texture_arrays(data);
	initialize_colors_arrays(data);
	data->map_looks.player_pos_parsed = false;
}
