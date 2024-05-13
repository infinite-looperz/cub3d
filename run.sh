name=dene

gcc dene.c MLX42/build/libmlx42.a -lglfw -ldl -pthread -lm -o $name
./$name