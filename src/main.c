#include <cub3d.h>

double	fix_angle(double angle)
{
	if (angle < 0)
		angle = fmod(angle, 2 * M_PI) + 2 * M_PI;
	else if (angle > (2 * M_PI))
		angle = fmod(angle, 2 * M_PI);
	return (angle);
}

int	way_check(double angle, double *step, double *way, char x_y)
{
	if((x_y == 'x' && (angle < M_PI / 2 || angle > 3 * M_PI / 2))
		|| (x_y == 'y' && (angle > 0 && angle < M_PI)))
	{
		*way += T_SIZE;
		return (1);
	}
	*step *= -1;
	return (-1);
}

bool	angle_check(double angle, char c)
{
	if ((c == 'x' && (angle > M_PI / 2 && angle < 3 * M_PI / 2))
		|| (c == 'y' && (angle > 0 && angle < M_PI)))
		return (true);
	return (false);
}

bool	wall_check(t_data *data, double x, double y)
{
	int	x_map;
	int	y_map;

	if (x < 0 || y < 0)
		return (true);
	x_map = x / T_SIZE;
	y_map = y / T_SIZE;
	if (y_map >= data->map_h || x_map >= data->map_w)
		return (true);
	if (data->map[y_map] && x_map <= strlen(data->map[y_map]))
		if (data->map[y_map][x_map] == '1')
			return (true);
	return (false);
}

double get_inter_x(t_data *data, double angle)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	int		x_way;

	x_step = T_SIZE;
	y_step = T_SIZE * tan(angle);
	x = data->plyr->real_x - (data->plyr->real_x % T_SIZE);
	x_way = way_check(angle, &x_step, &x, 'x');
	y = data->plyr->real_y + ((x - data->plyr->real_x) * tan(angle));
	if ((angle_check(angle, 'y') && y_step < 0) || (!angle_check(angle, 'y') && y_step > 0))
		y_step *= -1;
	while (!wall_check(data, x + x_way, y))
	{
		x += x_step;
		y += y_step;
	}
	return (sqrt(pow(x - data->plyr->real_x, 2) + pow(y - data->plyr->real_y, 2)));
}

double get_inter_y(t_data *data, double angle)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	int		y_way;

	x_step = T_SIZE / tan(angle);
	y_step = T_SIZE;
	y = data->plyr->real_y - (data->plyr->real_y % T_SIZE);
	y_way = way_check(angle, &y_step, &y, 'y');
	x = data->plyr->real_x + ((y - data->plyr->real_y) / tan(angle));
	if ((angle_check(angle, 'x') && x_step > 0) || (!angle_check(angle, 'x') && x_step < 0))
		x_step *= -1;
	while (!wall_check(data, x, y + y_way))
	{
		x += x_step;
		y += y_step;
	}
	return (sqrt(pow(x - data->plyr->real_x, 2) + pow(y - data->plyr->real_y, 2)));
}

void	put_lines(t_data *data, int line, double dist)
{
	double bot;
	double top;
	double size;

	dist *= cos(fix_angle(data->plyr->ray_ang - data->plyr->plyr_ang));
	size = (T_SIZE / dist) * ((D_W / 2) / tan(data->plyr->rad_fov / 2));
	top = (D_H / 2) - (size / 2);
	bot = (D_H / 2) + (size / 2);
	if (top < 0)
		top = 0;
	if (top > D_H / 2)
		top = D_H / 2;
	if (bot >= D_H)
		bot = D_H - 1;
	if (bot < D_H / 2)
		bot = D_H / 2 + 1;

	mlx_put_pixel(data->img, line, top, 0xff0000ff);
	mlx_put_pixel(data->img, line, bot, 0xff0000ff);
}

void	ray_casting(t_data *data)
{
	double dist;
	double x;
	double y;
	int line;

	line = 0;
	data->plyr->ray_ang = data->plyr->plyr_ang - data->plyr->rad_fov / 2;
	while (line < D_W)
	{
	x = get_inter_x(data, fix_angle(data->plyr->ray_ang));
	y = get_inter_y(data, fix_angle(data->plyr->ray_ang));
	data->plyr->flag = 0;
	if (x < y)
		dist = x;
	else
	{
		dist = y;
		data->plyr->flag = 1;
	}
	put_lines(data, line, dist);
	line++;
	data->plyr->ray_ang += data->plyr->rad_fov / D_W;
	}
}

void	move(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->plyr->plyr_ang += 0.03;
		if (data->plyr->plyr_ang > 2 * M_PI)
		{
			data->plyr->plyr_ang -= 2 * M_PI;
		}
		
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plyr->plyr_ang -= 0.03;
		if (data->plyr->plyr_ang < 0)
		{
			data->plyr->plyr_ang += 2 * M_PI;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->plyr->real_x = round(data->plyr->real_x + cos(data->plyr->plyr_ang) * 4);
		data->plyr->real_y = round(data->plyr->real_y + sin(data->plyr->plyr_ang) * 4);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->plyr->real_x = round(data->plyr->real_x - cos(data->plyr->plyr_ang) * 4);
		data->plyr->real_y = round(data->plyr->real_y - sin(data->plyr->plyr_ang) * 4);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->plyr->real_x = round(data->plyr->real_x + sin(data->plyr->plyr_ang) * 4);
		data->plyr->real_y = round(data->plyr->real_y - cos(data->plyr->plyr_ang) * 4);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->plyr->real_x = round(data->plyr->real_x - sin(data->plyr->plyr_ang) * 4);
		data->plyr->real_y = round(data->plyr->real_y + cos(data->plyr->plyr_ang) * 4);
	}
}

void color(mlx_image_t *img)
{
	int i = 0;
	while (i < D_W*D_H*4)
	{
		img->pixels[i++] = 0;
		img->pixels[i++] = 0;
		img->pixels[i++] = 0;
		img->pixels[i++] = 255;
	}
	
}

void	loop(void *par) 
{
	t_data	*data;

	data = par;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, D_W, D_H);
	color(data->img);
	ray_casting(data);
	move(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	player_init(t_data *data)
{
	data->plyr->real_x = data->plyr->x * T_SIZE - T_SIZE / 2;
	data->plyr->real_y = data->plyr->y * T_SIZE - T_SIZE / 2;
	data->plyr->rad_fov = FOV * M_PI / 180;
	data->plyr->plyr_ang = M_PI;
}

void	map(t_data *data)
{
	data->plyr = calloc(1, sizeof(t_player));
	data->map = calloc(10, sizeof(char *)); // init the map
	data->map[0] = strdup("1111111111111111111111111"); //fill the map
	data->map[1] = strdup("1000000000000000000100001");
	data->map[2] = strdup("1001000000000P00000000001");
	data->map[3] = strdup("1001000000000000001000001");
	data->map[4] = strdup("1001100000000000001000001");
	data->map[5] = strdup("1001000100010000000100001");
	data->map[6] = strdup("1001000000000000001000001");
	data->map[7] = strdup("1001110000001000001000001");
	data->map[8] = strdup("1111111111111111111111111");
	data->map[9] = NULL;
	data->plyr->x = 14;
	data->plyr->y = 2;
	data->map_h = 9;
	data->map_w = 25;
}

void esc(mlx_key_data_t key, void *param)
{
	if(key.key == MLX_KEY_ESCAPE)
		exit(0);
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
	data.mlx = mlx_init(D_W, D_H, "cub3D", true);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_key_hook(data.mlx, esc, NULL);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	// free_main_struct(&data);
	return 0;
}