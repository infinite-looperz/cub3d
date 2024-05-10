/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 17:43:02 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/10 19:56:43 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <MLX42/include/MLX42/MLX42.h>
# include <libft/libft.h>

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
	int			floor_color[3];
	int			ceiling_color[3];
	bool		NO_parsed;
	bool		SO_parsed;
	bool		WE_parsed;
	bool		EA_parsed;
	bool		F_parsed;
	bool		C_parsed;
}				t_map_looks;


typedef struct s_data
{
	mlx_image_t	*player;
	mlx_t		*mlx;
	char		**map_info;
	char		**map_coords;
	// bool		map_elements_parsed;
	t_map_looks	map_looks;
	size_t		map_height;
	size_t		map_width;
}				t_data;

/* Initialization */
void	data_init(t_data* data);

/* Validation */
void	validate_args(t_data *data, int arg_count, char **args);
void	validate_map(t_data *data, char *filename);


/* Free memory */
void	free_main_struct(t_data *data);
void	free_2D_array(void **array);
void	free_and_null(void *p);

/* Errors */
void	error_and_exit(t_data *data, char *s, int ierr);

/* Utilities */
bool	is_whitespace(char c);
void	*ft_calloc_cub3d(t_data *data, size_t count, size_t size);
char	**ft_split_cub3d(t_data *data, char const *s);
int		ft_atoi_cub3d(t_data *data, const char *str, char**	tmp, char**	tmp_2);
bool	check_parsing_stage(t_data *data);

#endif