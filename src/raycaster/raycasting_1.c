/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 16:37:28 by seyildir      #+#    #+#                 */
/*   Updated: 2024/06/10 18:59:45 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ray_casting_while(t_data *data, double x, double y, int line)
{
	double	dist;

	while (line < D_W)
	{
		x = get_inter_x(data, data->plyr->ray_ang, &data->direction_x);
		y = get_inter_y(data, data->plyr->ray_ang, &data->direction_y);
		data->plyr->flag = 0;
		if (x <= y)
		{
			dist = x;
			put_lines(data, line, dist, data->direction_x);
		}
		else
		{
			dist = y;
			data->plyr->flag = 1;
			put_lines(data, line, dist, data->direction_y);
		}
		line++;
		data->plyr->ray_ang = fix_angle(data->plyr->ray_ang \
		+ data->plyr->rad_fov / D_W);
	}
}

void	ray_casting(t_data *data)
{
	data->plyr->ray_ang = data->plyr->plyr_ang - data->plyr->rad_fov / 2;
	ray_casting_while(data, 0, 0, 0);
}

void	loop(void *par)
{
	t_data	*data;

	data = par;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, D_W, D_H);
	if (data->img == NULL)
		error_and_exit(data, "Malloc error\n", 42);
	ray_casting(data);
	move(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_terminate(data->mlx);
		error_and_exit(data, "Couldn't put image to window\n", 73);
	}
}
