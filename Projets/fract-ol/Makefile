# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 17:14:35 by tlebon            #+#    #+#              #
#    Updated: 2024/02/17 17:53:58 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

#COMPILATION#####################
CC = cc
CFLAGS = -Wall -Werror -Wextra
#################################

#SOURCES#########################
SRC_PATH = ./src
SRC = $(SRC_PATH)/main.c
OBJ = $(SRC.c=.o)
#################################

#LIBFT###########################
LIBFT_PATH = libs/libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)
#################################

#MLX#############################
MLX_PATH = /home/tlebon/Desktop/Transfert/Projets/fract-ol/libs/mlx
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)
#################################

#INCLUDES########################
INC =	-I ./includes\
		-I ./includes/libft\
		-I ./includes/mlx\
#################################
tryout: $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -L $(MLX_PATH) -lmlx -lXext -lX11 -L $(LIBFT_PATH) -lft

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	make -C $(MLX_PATH)
$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ)  
	$(CC) $(CFLAGS)-o $(NAME) $(OBJ) -L $(MLX_PATH) -lmlx -lXext -lX11


#cc -Wall -Werror -Wextra source/main.c -L /home/tlebon/Desktop/Transfert/Projets/fract-ol/library/mlx -lmlx -lXext -lX11



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
