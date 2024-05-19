# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akasiota <akasiota@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/03/15 17:23:44 by akasiota      #+#    #+#                  #
#    Updated: 2024/05/15 18:10:59 by akasiota      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME := cub3d
CC := cc
MLX42 := MLX42/build/libmlx42.a
LIBFT := libft/libft.a

CFLAGS := -Wall -Wextra -Werror -g
LIBS := $(LIBFT) $(MLX42)

OS := $(shell uname)

ifeq ($(OS), Darwin)
	EXT = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

ifeq ($(OS), Linux)
	EXT = -lglfw -ldl -pthread -lm
endif

SRC_DIR := ./src

OBJ_DIR := ./obj
# SRC = $(wildcard $(SRC_DIR)/**/*.c)
SRC :=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/map_init.c \
		$(SRC_DIR)/parser/parser.c \
		$(SRC_DIR)/parser/parser_utils.c \
		$(SRC_DIR)/parser/parser_utils_2.c \
		$(SRC_DIR)/parser/validation.c \
		$(SRC_DIR)/parser/validate_args.c \
		$(SRC_DIR)/utilities/free_memory.c \
		$(SRC_DIR)/utilities/ft_calloc_cub3d.c \
		$(SRC_DIR)/utilities/ft_split_cub3d.c \
		$(SRC_DIR)/utilities/ft_atoi_cub3d.c \
		$(SRC_DIR)/utilities/errors.c \
		$(SRC_DIR)/utilities/utilities.c
# OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ :=	$(OBJ_DIR)/main.o \
		$(OBJ_DIR)/map_init.o \
		$(OBJ_DIR)/parser/parser.o \
		$(OBJ_DIR)/parser/parser_utils.o \
		$(OBJ_DIR)/parser/parser_utils_2.o \
		$(OBJ_DIR)/parser/validation.o \
		$(OBJ_DIR)/parser/validate_args.o \
		$(OBJ_DIR)/utilities/free_memory.o \
		$(OBJ_DIR)/utilities/ft_calloc_cub3d.o \
		$(OBJ_DIR)/utilities/ft_split_cub3d.o \
		$(OBJ_DIR)/utilities/ft_atoi_cub3d.o \
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

.PHONY: fclean clean re all