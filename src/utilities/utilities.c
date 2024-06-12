/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 17:31:48 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/12 16:55:32 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	empty_until_end(t_data *data, size_t i)
{
	if (data->map_i[i + 1] == NULL || data->map_i[i + 1][0] == '\0')
		return (true);
	i++;
	while (data->map_i[i] != NULL)
	{
		if (data->map_i[i][0] == '\n')
			i++;
		else
			return (false);
	}
	if (data->map_i[i] == NULL)
		return (true);
	return (false);
}

/* Here for testing only */
// void	print_stored_info(t_data *data)
// {
// 	size_t	i;

// 	i = 0;
// 	printf("\n-----------Map info-----------\n");
// 	while (data->map_i[i] != NULL)
// 	{
// 		ft_printf("%s", data->map_i[i]);
// 		i++;
// 	}
// 	i = 0;
// 	printf("\n-----------Texture files-----------\n");
// 	while (data->map_looks.textures[i] != NULL && i < 4)
// 	{
// 		printf("%s\n", data->map_looks.textures[i]);
// 		i++;
// 	}
// 	i = 0;
// 	printf("\n-----------Colors-----------\n");
// 	printf("floor: %u\n", data->map_looks.floor_c);
// 	printf("ceiling: %u\n", data->map_looks.ceiling_c);
// 	i = 0;
// 	printf("\n-----------Map-----------\n");
// 	while (i < data->map_h)
// 	{
// 		printf("%lu:	%s\n", i, data->map_c[i]);
// 		i++;
// 	}
// }
