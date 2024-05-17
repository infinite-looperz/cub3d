#include <cub3d.h>

#define DPS_W 1900
#define DPS_H 1100


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

void	ray_cast(void *par)
{
	t_data	*data;

	data = par;
	mlx_delete_image(data->mlx, data->player);
	data->player = mlx_new_image(data->mlx, DPS_W, DPS_H);
	int y;
	int x;
	x = 100;
	while (x < 700)
	{
		y = 100;
		while (y < 500)
		{
			mlx_put_pixel(data->player, x, y++, 0xff0000ff);
		}
		x++;
	}
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
	data.mlx = mlx_init(DPS_W, DPS_H, "cub3D", true);
	// mlx_key_hook(data.mlx, move, &data);
	data.x = 100;
	mlx_loop_hook(data.mlx, ray_cast, &data);
	// mlx_loop_hook(data.mlx, move, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return 0;
}