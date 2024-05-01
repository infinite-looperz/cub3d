#include <cub3d.h>

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}


int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 500, 500)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


/* #define VERTICAL 0
#define HORIZONTAL 1
// #define MLX data->mlx

void moves(t_data *data, int dist, int drct)
{
	if (drct)
		data->player->instances[0].x += dist;
	else
		data->player->instances[0].y += dist;
}

void move(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_W)
			moves(data, -10, VERTICAL);
		else if (key.key == MLX_KEY_S)
			moves(data, 10, VERTICAL);
		else if (key.key == MLX_KEY_A)
			moves(data, -10, HORIZONTAL);
		else if (key.key == MLX_KEY_D)
			moves(data, 10, HORIZONTAL);
		else if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);
	}
}

int	map_build(t_data *data)
{
	data->player = mlx_new_image(data->mlx, 10, 10);
	ft_memset(data->player->pixels, 255, 400);
	mlx_image_to_window(data->mlx, data->player, 750, 500);
}

int main(int argc, char const *argv[])
{
	t_data	data;
	// map_init();
	printf("%ld\n", sizeof(int32_t));
	data.mlx = mlx_init(1500, 1000, "cub3D", true);
	map_build(&data);
	mlx_key_hook(data.mlx, move, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return 0;
} */

