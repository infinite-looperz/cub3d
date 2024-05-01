#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <MLX42/include/MLX42/MLX42.h>
# include <libft/libft.h>

typedef struct s_data
{
	mlx_image_t	*player;
	mlx_t		*mlx;
}				t_data;

#endif