/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 14:54:52 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/28 13:13:04 by akasiota      ########   odam.nl         */
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

void	free_2d_array(void **array)
{
	int	i;

	i = 0;
	while (array != NULL && array[i] != NULL)
	{
		free_and_null(&array[i]);
		array[i] = NULL;
		i++;
	}
	if (array != NULL)
	{
		free(array);
		array = NULL;
	}
}

void	free_main_struct(t_data *data)
{
	int	i;
	/* Make sure that it is updated for memory freeing */
	free_2d_array((void **)data->map_i);
	free_2d_array((void **)data->map_c);
	free_and_null((void**)&data->plyr);
	i = 0;
	while (i < 4)
	{
		free_and_null((void **)&data->map_looks.textures[i]);
		i++;
	}
}
