#include <cub3d.h>

#define PLAYER_SPD 4
#define ROTATE_SPD 0.03

void	move(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->plyr->plyr_ang += ROTATE_SPD;
		if (data->plyr->plyr_ang > 2 * M_PI)
		{
			data->plyr->plyr_ang -= 2 * M_PI;
		}
		
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plyr->plyr_ang -= ROTATE_SPD;
		if (data->plyr->plyr_ang < 0)
		{
			data->plyr->plyr_ang += 2 * M_PI;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->plyr->real_x = round(data->plyr->real_x + cos(data->plyr->plyr_ang) * PLAYER_SPD);
		data->plyr->real_y = round(data->plyr->real_y + sin(data->plyr->plyr_ang) * PLAYER_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->plyr->real_x = round(data->plyr->real_x - cos(data->plyr->plyr_ang) * PLAYER_SPD);
		data->plyr->real_y = round(data->plyr->real_y - sin(data->plyr->plyr_ang) * PLAYER_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->plyr->real_x = round(data->plyr->real_x + sin(data->plyr->plyr_ang) * PLAYER_SPD);
		data->plyr->real_y = round(data->plyr->real_y - cos(data->plyr->plyr_ang) * PLAYER_SPD);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->plyr->real_x = round(data->plyr->real_x - sin(data->plyr->plyr_ang) * PLAYER_SPD);
		data->plyr->real_y = round(data->plyr->real_y + cos(data->plyr->plyr_ang) * PLAYER_SPD);
	}
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