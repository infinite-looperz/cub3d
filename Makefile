# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: seyildir <seyildir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/03/15 17:23:44 by akasiota      #+#    #+#                  #
#    Updated: 2024/06/12 16:56:27 by akasiota      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME := cub3d
CC := gcc
MLX42 := MLX42/build/libmlx42.a
LIBFT := libft/libft.a

CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
LIBS := $(LIBFT) $(MLX42)

OS := $(shell uname)

ifeq ($(OS), Darwin)
	EXT = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

ifeq ($(OS), Linux)
	EXT = -lglfw -ldl -pthread -lm
endif

SRC_DIR := ./src
PARSER_DIR := $(SRC_DIR)/parser
RAYCAST_DIR := $(SRC_DIR)/raycaster
UTIL_DIR := $(SRC_DIR)/utilities
OBJ_DIR := ./obj

SRC :=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/map_init.c \
		$(PARSER_DIR)/parser.c \
		$(PARSER_DIR)/parser_utils.c \
		$(PARSER_DIR)/parser_utils_2.c \
		$(PARSER_DIR)/validation.c \
		$(PARSER_DIR)/validation_2.c \
		$(PARSER_DIR)/validate_args.c \
		$(RAYCAST_DIR)/raycasting_1.c \
		$(RAYCAST_DIR)/raycasting_2.c \
		$(RAYCAST_DIR)/raycasting_3.c \
		$(RAYCAST_DIR)/raycasting_4.c \
		$(RAYCAST_DIR)/movement.c \
		$(UTIL_DIR)/free_memory.c \
		$(UTIL_DIR)/ft_calloc_cub3d.c \
		$(UTIL_DIR)/ft_split_cub3d.c \
		$(UTIL_DIR)/cub3d_atoi.c \
		$(UTIL_DIR)/errors.c \
		$(UTIL_DIR)/utilities.c

OBJ :=	$(OBJ_DIR)/main.o \
		$(OBJ_DIR)/map_init.o \
		$(OBJ_DIR)/parser/parser.o \
		$(OBJ_DIR)/parser/parser_utils.o \
		$(OBJ_DIR)/parser/parser_utils_2.o \
		$(OBJ_DIR)/parser/validation.o \
		$(OBJ_DIR)/parser/validation_2.o \
		$(OBJ_DIR)/parser/validate_args.o \
		$(OBJ_DIR)/raycaster/raycasting_1.o \
		$(OBJ_DIR)/raycaster/raycasting_2.o \
		$(OBJ_DIR)/raycaster/raycasting_3.o \
		$(OBJ_DIR)/raycaster/raycasting_4.o \
		$(OBJ_DIR)/raycaster/movement.o \
		$(OBJ_DIR)/utilities/free_memory.o \
		$(OBJ_DIR)/utilities/ft_calloc_cub3d.o \
		$(OBJ_DIR)/utilities/ft_split_cub3d.o \
		$(OBJ_DIR)/utilities/cub3d_atoi.o \
		$(OBJ_DIR)/utilities/errors.o \
		$(OBJ_DIR)/utilities/utilities.o

RM := rm -f

all: $(MLX42) $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	cc $(CFLAGS) -o $@ -c $< -I ./
	
$(NAME): $(OBJ)
	cc $(CFLAGS) -o $@ $(OBJ) -I ./ $(LIBS) $(EXT)
	@echo $(NAME) creating...

$(LIBFT):
	make -C libft

$(MLX42):
	cd MLX42 && cmake -B build && cmake --build build -j4

fclean:
	make -C libft fclean
	$(RM)r MLX42/build
	$(RM) $(NAME)
	$(RM)r $(OBJ_DIR)

clean:
	make -C libft clean
	$(RM)r $(OBJ_DIR)


re: fclean all

# push: fclean
# 	git add .
# 	git commit -m "update"
# 	git push

# commit: fclean
# 	git add .
# 	git commit -m "update"

.PHONY: fclean clean re all push