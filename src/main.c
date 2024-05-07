#include <cub3d.h>

#define VERTICAL 0
#define HORIZONTAL 1
// #define MLX data->mlx

void moves(t_data *data, int dist, int drct)
{
	if (drct)
		data->player->instances[0].x += dist;
	else
		data->player->instances[0].y += dist;
}

void move(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		moves(data, -1, VERTICAL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		moves(data, 1, VERTICAL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		moves(data, 1, HORIZONTAL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		moves(data, -1, HORIZONTAL);
}

int	map_build(t_data *data)
{
	data->player = mlx_new_image(data->mlx, 10, 10);
	ft_memset(data->player->pixels, 255, 400);
	mlx_image_to_window(data->mlx, data->player, 750, 500);
	return (0);
}

int main(int argc, char *argv[])
{
	t_data	data;
	// map_init();
	data_init(&data);
	validate_args(&data, argc, argv);
	validate_map(&data, argv[1]);
	// printf("%ld\n", sizeof(int32_t));
	// data.mlx = mlx_init(1500, 1000, "cub3D", true);
	// map_build(&data);
	// // mlx_key_hook(data.mlx, move, &data);
	// mlx_loop_hook(data.mlx, move, &data);
	// mlx_loop(data.mlx);
	// mlx_terminate(data.mlx);
	free_main_struct(&data);
	return 0;
}

