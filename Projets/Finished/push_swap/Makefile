# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 13:25:15 by tlebon            #+#    #+#              #
#    Updated: 2024/05/22 18:47:12 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

#COMPILATION###################
CC = cc
CFLAGS = -Wall -Werror -Wextra
###############################

#SOURCES#######################
SRC_PATH = ./src
SRC =								\
		$(SRC_PATH)/main.c			\
		$(SRC_PATH)/nodes.c			\
		$(SRC_PATH)/instructions.c	\
		$(SRC_PATH)/sort.c			\
		$(SRC_PATH)/refresh.c		\
		$(SRC_PATH)/push_swap.c		\
###############################

#LIBFT#########################
LIBFT_PATH = lib
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_LINK = -L $(LIBFT_PATH) -lft
###############################

OBJ = $(SRC:.c=.o)

all: lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_LINK)
	
lib : 
	make -C $(LIBFT_PATH) libft.a

libclean:
	make -C $(LIBFT_PATH) clean

libfclean:
	make -C $(LIBFT_PATH) fclean

clean: libclean
	rm -rf $(OBJ)

fclean: libfclean clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all lib libclean clean libfclean fclean re
