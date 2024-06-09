/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_atoi.c                                    	:+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 19:55:05 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/09 18:07:30 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

uint32_t	cub3d_atoi(t_data *data, const char *str, char **tmp, char **tmp_2)
{
	short int	sy;
	int			i;
	long long	r;

	r = 0;
	i = 0;
	sy = 1;
	if (str == NULL)
	{
		free_2d_array((void **)tmp_2);
		free_2d_array((void **)tmp);
		error_and_exit(data, "Atoi for cub3d failed because str is NULL", 84);
	}
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '-')
		sy = -sy;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		r = (r * 10) + (str[i++] - '0');
	if ((long long)(r * sy) > 255 || (long long)(r * sy) < 0)
		error_and_exit(data, "Color values out of range\n", 85);
	return ((uint32_t)(r * sy));
}
