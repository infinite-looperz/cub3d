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
		moves(data, -5, VERTICAL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		moves(data, 5, VERTICAL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		moves(data, 5, HORIZONTAL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		moves(data, -5, HORIZONTAL);
}

void make_color(mlx_image_t *p, int x, int y)
{
	int i = 0;
	while (i < (x*y*(int)sizeof(uint32_t)))
	{
		p->pixels[i++] = 255;
		p->pixels[i++] = 255;
		p->pixels[i++] = 0;
		p->pixels[i++] = 255;
	}
	
}

int	map_build(t_data *data)
{
	int px;
	int py;

	px = 15;
	py = 15;
	data->player = mlx_new_image(data->mlx, px, py);
	make_color(data->player, px, py);
	mlx_image_to_window(data->mlx, data->player, 750, 500);
}

int main(int argc, char const *argv[])
{
	t_data	data;

	// map_init();
	printf("%ld\n", sizeof(int32_t));
	data.mlx = mlx_init(1500, 1000, "cub3D", true);
	map_build(&data);
	// mlx_key_hook(data.mlx, move, &data);
	mlx_loop_hook(data.mlx, move, &data);
	// mlx_loob_hook(data.mlx, ray_cast, );
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return 0;
}

