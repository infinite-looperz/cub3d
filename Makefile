# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akasiota <akasiota@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/03/15 17:23:44 by akasiota      #+#    #+#                  #
#    Updated: 2024/05/07 16:42:10 by akasiota      ########   odam.nl          #
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
# SRC = $(wildcard $(SRC_DIR)/*.c)
SRC :=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/map_init.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/free_memory.c \
		$(SRC_DIR)/errors.c
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

RM := rm -f

all: $(MLX42) $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
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