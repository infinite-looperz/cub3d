#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <MLX42/include/MLX42/MLX42.h>
# include <libft/libft.h>

typedef	enum	e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_direction;

typedef enum	e_color
{
	RED,
	GREEN,
	BLUE
}				t_color;

typedef struct s_map_looks
{
	char*		textures[4];
	int			floor_color[3];
	int			ceiling_color[3];
}				t_map_looks;


typedef struct s_data
{
	mlx_image_t	*player;
	mlx_t		*mlx;
	char**		map_info;
	t_map_looks	map_looks;
}				t_data;

/* Validation */
void	validate_args(int arg_count, char** args);
void	validate_map(t_data *data, char* filename);


/* Free memory */
void	free_main_struct(t_data* data);
void	free_2D_array(void** array);

#endif