/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_cub3d.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 19:55:05 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/07 20:12:10 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_atoi_cub3d(t_data *data, const char *str, char **tmp, char **tmp_2)
{
	short int	sy;
	int			i;
	long		r;

	r = 0;
	i = 0;
	sy = 1;
	if (str == NULL)
	{
		free_2D_array((void **)tmp_2);
		free_2D_array((void **)tmp);
		error_and_exit(data, "Atoi for cub3d failed because str NULL", 7);
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
	return ((int)(r * sy));
}
