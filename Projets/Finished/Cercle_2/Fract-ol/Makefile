# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 17:14:35 by tlebon            #+#    #+#              #
#    Updated: 2024/06/20 18:08:44 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

#COMPILATION#####################
CC = cc
CFLAGS = -Wall -Werror -Wextra
#################################

#SOURCES#########################
SRC_PATH = ./src
SRC = 										\
		$(SRC_PATH)/main.c					\
		$(SRC_PATH)/constructors.c			\
		$(SRC_PATH)/constructors_utils.c	\
		$(SRC_PATH)/utils.c					\
		$(SRC_PATH)/grad.c					\
		$(SRC_PATH)/setters.c				\
		$(SRC_PATH)/hooks.c					\
		$(SRC_PATH)/fractal.c				\
#################################

#LIBFT###########################
LIBFT_PATH = libs/libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)
LIBFT_LINK = -L $(LIBFT_PATH) -lft
#################################

#MLX#############################
MLX_PATH = libs/mlx
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)
MLX_LINK = -L $(MLX_PATH) -lmlx -lXext -lX11
#################################

#OTHER###########################
OTHER_LINK = -lm
#################################

OBJ = $(SRC:.c=.o)

all: mlx lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_LINK) $(LIBFT_LINK) $(OTHER_LINK)

mlx:
	make -C $(MLX_PATH)

lib:
	make -C $(LIBFT_PATH) libft.a

libclean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
libfclean:
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX_PATH) clean

clean: libclean
	rm -rf $(OBJ)

fclean: clean libfclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all mlx lib libclean libfclean clean fclean re
