/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/09 15:55:00 by seyildir      #+#    #+#                 */
/*   Updated: 2024/06/09 19:38:05 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	esc(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(data->mlx);
		free_main_struct(data);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data_init(&data);
	validate_args(&data, argc, argv);
	open_and_store(&data, argv[1]);
	validate_map(&data);
	player_init(&data);
	data.mlx = mlx_init(D_W, D_H, "cub3D", true);
	if (data.mlx == NULL)
		error_and_exit(&data, "Malloc error\n", 42);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_key_hook(data.mlx, esc, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_main_struct(&data);
	return (0);
}
