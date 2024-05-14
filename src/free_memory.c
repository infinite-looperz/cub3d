/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 14:54:52 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/10 20:16:50 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_and_null(void **p)
{
	if (*p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}

void	free_2D_array(void **array)
{
	int	i;

	i = 0;
	while (array != NULL && array[i] != NULL)
	{
		free_and_null(&array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_main_struct(t_data *data)
{
	/* Make sure that it is updated for memory freeing */
	int i;
	
	free_2D_array((void**)data->map_info);
	free_2D_array((void**)data->map_coords);
	i = 0;
	while (i < 4)
	{
		free_and_null((void**)&data->map_looks.textures[i]);
		i++;
	}
}