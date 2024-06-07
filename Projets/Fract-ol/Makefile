# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 17:14:35 by tlebon            #+#    #+#              #
#    Updated: 2024/05/28 19:51:08 by tlebon           ###   ########.fr        #
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

all: $(MLX) lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_LINK) $(LIBFT_LINK) $(OTHER_LINK)

debug: $(MLX) lib
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(MLX_LINK) $(LIBFT_LINK) $(OTHER_LINK)
	
$(MLX):
	make -C $(MLX_PATH)

lib:
	make -C $(LIBFT_PATH) libft.a

libftclean:
	make -C $(LIBFT_PATH) clean
libftfclean:
	make -C $(LIBFT_PATH) fclean

clean: libftclean
	rm -rf $(OBJ)

fclean: clean libftfclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
