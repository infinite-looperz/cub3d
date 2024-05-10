/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 15:58:47 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/10 15:59:08 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	validate_args(t_data* data, int arg_count, char** args)
{
	int	map_name_len;
	int	i;

	if (arg_count != 2)
		error_and_exit(data, "Usage: ./cub3d [filename]\n", 1);
	map_name_len = ft_strlen(args[1]);
	i = 0;
	if (map_name_len > 4)
	{
		while ((map_name_len - i) > 4)
			i++;
		if (ft_strncmp(&args[1][i], ".cub", 4) != 0)
			error_and_exit(data, "Filename extension needs to be .cub\n", 2);
	}
	else
		error_and_exit(data, "Filename needs extension .cub\n", 3);
	return ;
}
