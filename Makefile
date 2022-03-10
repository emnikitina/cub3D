# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: odomenic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 19:00:57 by odomenic          #+#    #+#              #
#    Updated: 2021/03/23 20:07:05 by odomenic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS_MLX = -framework OpenGL -framework Appkit
LIBFT_DIR = libft
MLX_DIR = minilibx_opengl_20191021
SRCS = get_next_line.c \
	   ft_read_file.c \
	   ft_read_map.c \
	   ft_error_one.c \
	   ft_error_two.c \
	   ft_get_params.c \
	   ft_valid.c \
	   ft_raycasting.c \
	   ft_textures.c \
	   ft_sprites.c \
	   ft_window.c \
	   ft_draw.c \
	   ft_mlx_units.c \
	   ft_keypress.c \
	   ft_move.c \
	   ft_rotate.c \
	   main.c \
	   ft_screenshot.c \
	   ft_clean.c \
	   ft_utils.c \

OBJ = $(SRCS:.c=.o)
RM = rm -f
NAME = cub3D

%.o: %.c cub3d.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(FLAGS_MLX) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)


fclean:
	$(RM) $(NAME) $(OBJ)
	make clean -C $(MLX_DIR)
	make fclean -C $(LIBFT_DIR)


re: fclean all
