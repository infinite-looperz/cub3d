#include <cub3d.h>

#define PLYR_SPD 4
#define ROT_SPD 0.03

void	move_check(t_data *data, int x, int y)
{
	int map_x;
	int map_y;

	map_x = x / T_SIZE;
	map_y = y / T_SIZE;
	if ((size_t)map_y >= data->map_h || (size_t)map_x >= data->map_w)
		return ;
	if (data->map_c[map_y][map_x] == '1')
		return ;
	data->plyr->real_x = x;
	data->plyr->real_y = y;
}


void move(t_data *data)
{
	int x;
	int y;

	x = data->plyr->real_x;
	y = data->plyr->real_y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->plyr->plyr_ang += ROT_SPD;
		if (data->plyr->plyr_ang > 2 * M_PI)
		{
			data->plyr->plyr_ang -= 2 * M_PI;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plyr->plyr_ang -= ROT_SPD;
		if (data->plyr->plyr_ang < 0)
		{
			data->plyr->plyr_ang += 2 * M_PI;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		x += round(cos(data->plyr->plyr_ang) * PLYR_SPD);
		y += round(sin(data->plyr->plyr_ang) * PLYR_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		x -= round(cos(data->plyr->plyr_ang) * PLYR_SPD);
		y -= round(sin(data->plyr->plyr_ang) * PLYR_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		x += round(sin(data->plyr->plyr_ang) * PLYR_SPD);
		y -= round(cos(data->plyr->plyr_ang) * PLYR_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		x -= round(sin(data->plyr->plyr_ang) * PLYR_SPD);
		y += round(cos(data->plyr->plyr_ang) * PLYR_SPD);
	}
	move_check(data, x, y);
}

void	player_init(t_data *data)
{
	data->plyr->real_x = data->plyr->x * T_SIZE + T_SIZE / 2;
	data->plyr->real_y = data->plyr->y * T_SIZE + T_SIZE / 2;
	data->plyr->rad_fov = FOV * M_PI / 180;
}

void esc(mlx_key_data_t key, void *param)
{
	t_data	*data;
	
	data = (t_data *)param;
	if(key.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(data->mlx);
		free_main_struct(data);
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	t_data	data;

	data_init(&data);
	validate_args(&data, argc, argv);
	open_and_store(&data, argv[1]);
	validate_map(&data);
	player_init(&data);
	data.mlx = mlx_init(D_W, D_H, "cub3D", true);
	if (data.mlx == NULL)
		error_and_exit(&data, "Memory allocation error\n", 42);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_key_hook(data.mlx, esc, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_main_struct(&data);
	return 0;
}