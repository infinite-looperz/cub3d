#include <cub3d.h>

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
		moves(data, -1, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		moves(data, 1, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		moves(data, 1, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		moves(data, -1, 1);
}

int	map_build(t_data *data)
{
	data->player = mlx_new_image(data->mlx, 1500, 1000);
	ft_memset(data->player->pixels, 255, 1500*1000*4);
	mlx_image_to_window(data->mlx, data->player, 0, 0);
}

int	map_init(t_data *data)
{
	data->map = calloc(10, sizeof(char *)); // init the map
	data->map[0] = strdup("1111111111111111111111111"); //fill the map
	data->map[1] = strdup("1000000000000000000100001");
	data->map[2] = strdup("1001000000000P00000000001");
	data->map[3] = strdup("1001000000000000001000001");
	data->map[4] = strdup("1001000000000000001000001");
	data->map[5] = strdup("1001000000100000001000001");
	data->map[6] = strdup("1001000000000000001000001");
	data->map[7] = strdup("1001000000001000001000001");
	data->map[8] = strdup("1111111111111111111111111");
	data->map[9] = NULL;
	// data->p_y = 3; // player y position in the map
	// data->p_x = 14; // player x position in the map
	// data->w_map = 25; // map width
	// data->h_map = 9; // map height
}

int main(int argc, char const *argv[])
{
	t_data	data;
	map_init(&data);
	data.mlx = mlx_init(1500, 1000, "cub3D", true);
	map_build(&data);
	// mlx_key_hook(data.mlx, move, &data);
	mlx_loop_hook(data.mlx, move, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return 0;
}