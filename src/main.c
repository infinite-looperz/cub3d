#include <cub3d.h>

double get_inter_x(t_data *data)
{
	data->plyr->real_x;
}

double get_inter_y(t_data *data)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	
	x_inter = data->plyr->real_x - (data->plyr->real_x % T_SIZE);
	printf("%f\n", x_inter);
	y_inter = (x_inter - data->plyr->real_x) * tan(data->plyr->ray_ang);
	return(y_inter);
}


void	get_inters(t_data *data)
{
	double x;
	double y;
	data->plyr->ray_ang = data->plyr->plyr_ang - data->plyr->rad_fov / 2;
	y = get_inter_y(data);
	// x = get_inter_x(data);
	printf("%f\n", y);
}

void	ray_cast(void *par)
{
	t_data	*data;

	data = par;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, D_W, D_H);
	int y;
	int x;
	x = 100;
	while (x < 700)
	{
		y = 100;
		while (y < 500)
		{
			mlx_put_pixel(data->img, x, y++, 0xff0000ff);
		}
		x++;
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	player_init(t_data *data)
{
	data->plyr->real_x = data->plyr->x * T_SIZE - T_SIZE / 2;
	data->plyr->real_y = data->plyr->y * T_SIZE - T_SIZE / 2;
	data->plyr->rad_fov = FOV * M_PI / 180;
	data->plyr->plyr_ang = M_PI;
	// data->plyr->ray_ang = 
}

void	map(t_data *data)
{
	data->plyr = calloc(1, sizeof(t_player));
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
	data->plyr->x = 14;
	data->plyr->y = 3;
}

int main(int argc, char *argv[])
{
	t_data	data;
	(void)argc;
	(void)argv;
	// validate_args(&data, argc, argv);
	// open_and_store(&data, argv[1]);
	// validate_map(&data);
	map(&data);
	player_init(&data);
	get_inters(&data);
	data.mlx = mlx_init(D_W, D_H, "cub3D", true);
	mlx_loop_hook(data.mlx, ray_cast, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	// free_main_struct(&data);
	return 0;
}