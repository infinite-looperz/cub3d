/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 16:41:19 by akasiota      #+#    #+#                 */
/*   Updated: 2024/06/09 15:54:13 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error_and_exit(t_data *data, char *s, int ierr)
{
	free_main_struct(data);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	exit(ierr);
}
