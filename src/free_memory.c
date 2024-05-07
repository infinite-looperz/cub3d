/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 14:54:52 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/07 17:15:36 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_2D_array(void** array)
{
	int	i;

	i = 0;
	while (array != NULL && array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_main_struct(t_data* data)
{
	/* Make sure that it is updated for memory freeing */
	int i;
	
	free_2D_array((void**)data->map_info);
	i = 0;
	while (i < 4)
	{
		free(data->map_looks.textures[i]);
		i++;
	}
}