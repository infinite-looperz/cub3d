/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 17:31:48 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/10 20:40:10 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	check_parsing_stage(t_data *data)
{
	if (data->map_looks.direction_parsed[NORTH] == true \
	&& data->map_looks.direction_parsed[SOUTH] == true \
	&& data->map_looks.direction_parsed[WEST] == true \
	&& data->map_looks.direction_parsed[EAST] == true \
	&& data->map_looks.F_parsed == true && data->map_looks.C_parsed == true)
		return (true);
	return (false);
}
