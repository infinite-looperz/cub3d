/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 17:43:02 by akasiota      #+#    #+#                 */
/*   Updated: 2024/05/07 20:05:02 by akasiota      ########   odam.nl         */
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
}				t_map_looks;


typedef struct s_data
{
	mlx_image_t	*player;
	mlx_t		*mlx;
	char		**map_info;
	bool		map_elements_parsed;
	t_map_looks	map_looks;
}				t_data;

/* Initialization */
void	data_init(t_data* data);

/* Validation */
void	validate_args(t_data *data, int arg_count, char **args);
void	validate_map(t_data *data, char *filename);


/* Free memory */
void	free_main_struct(t_data *data);
void	free_2D_array(void **array);

/* Errors */
void	error_and_exit(t_data *data, char *s, int ierr);

/* Utilities */
bool	is_whitespace(char c);
char	**ft_split_cub3d(t_data *data, char const *s);
int		ft_atoi_cub3d(t_data *data, const char *str, char**	tmp, char**	tmp_2);


#endif