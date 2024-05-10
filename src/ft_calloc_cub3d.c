/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_cub3d.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/19 19:44:51 by seyildir      #+#    #+#                 */
/*   Updated: 2024/05/10 17:25:52 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*ft_calloc_cub3d(t_data *data, size_t count, size_t size)
{
	void	*mem;

	mem = (void *) malloc (size * count);
	if (!mem)
		error_and_exit(data, "Malloc error\n", 42);
	ft_bzero(mem, count * size);
	return (mem);
}
