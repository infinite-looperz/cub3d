/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 16:50:33 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/07 16:53:33 by akasiota      ########   odam.nl         */
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
	while (i < 4)
	{
		data->map_looks.textures[i] = NULL;
		i++;
	}
}