/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 16:41:19 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/10 15:04:20 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error_and_exit(t_data* data, char* s, int ierr)
{
	/* Make sure that it is updated for memory freeing */
	free_main_struct(data);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	exit(ierr);
}
