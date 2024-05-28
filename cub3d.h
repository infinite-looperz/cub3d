/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 17:43:02 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/28 13:12:03 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <MLX42/include/MLX42/MLX42.h>
# include <libft/libft.h>

#define D_W 1900
#define D_H 1000
#define FOV 60
#define T_SIZE 30

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}			t_direction;

typedef enum e_color
{
	RED,
	GREEN,
	BLUE
}			t_color;

typedef struct s_map_looks
{
	char		*textures[4];
	int			floor_c[3];
	int			ceiling_c[3];
	bool		direction_parsed[4];
	bool		f_parsed;
	bool		c_parsed;
	bool		player_pos_parsed;
}				t_map_looks;

typedef	struct s_player
{
	double	rad_fov;
	double	plyr_ang;
	double	ray_ang;
	int		flag;
	int		x;
	int		y;
	int		real_x;
	int		real_y;
}				t_player;


typedef struct s_data
{
	mlx_image_t	*img;
	mlx_t		*mlx;
	char		**map_i;
	char		**map_c;
	t_map_looks	map_looks;
	size_t		map_h;
	size_t		map_w;
	t_player	*plyr;
}				t_data;

/* Initialization */
void	data_init(t_data *data);

/* Parsing */
void	open_and_store(t_data *data, char *filename);

/* Parsing utils */
void	store_map_info(t_data *data);
void	get_txtr(t_data *data, t_direction direction, char **tmp, size_t i);
void	store_coordinates(t_data *data, size_t i);
void	validate_colors(t_data *data);

/* Validation */
void	validate_args(t_data *data, int arg_count, char **args);
void	validate_map(t_data *data);

/* Free memory */
void	free_main_struct(t_data *data);
void	free_2d_array(void **array);
void	free_and_null(void **p);

/* Errors */
void	error_and_exit(t_data *data, char *s, int ierr);

/* Utilities */
void	print_stored_info(t_data *data);
bool	is_whitespace(char c);
void	*ft_calloc_cub3d(t_data *data, size_t count, size_t size);
char	**ft_split_cub3d(t_data *data, char const *s);
int		ft_atoi_cub3d(t_data *data, const char *str, char **tmp, char **tmp_2);
bool	check_parsing_stage(t_data *data);

#endif