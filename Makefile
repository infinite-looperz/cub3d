# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akasiota <akasiota@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/03/15 17:23:44 by akasiota      #+#    #+#                  #
#    Updated: 2024/04/24 15:36:31 by akasiota      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


CFLAGS := -Wall -Wextra -Werror
MLX42_DIR := MLX42
MLX42_LIB := MLX42/build/libmlx42.a

$(MLX42_LIB): $(MLX42_DIR)
	cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	cmake --build $(MLX42_DIR)/build -j4

all: $(MLX42_LIB)

clean:
	rm -rf $(MLX42_DIR)/build

fclean: clean

re: fclean all

.PHONY: all clean