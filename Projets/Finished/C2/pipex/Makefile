# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 18:19:46 by tlebon            #+#    #+#              #
#    Updated: 2024/07/22 14:44:48 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex


## COMPILATION ###############

CC = cc
CFLAGS = -Wall -Werror -Wextra
##############################

## HEADER ###

HDR = pipex.h
HDRB = bonus/pipex_bonus.h
#############

## SRC ##################################

SRC_PATH = src
SRC =							\
		$(SRC_PATH)/main.c		\
		$(SRC_PATH)/utils.c		\
		$(SRC_PATH)/file_pipe.c	\
		$(SRC_PATH)/exec.c		\

SRCB_PATH = bonus/src_bonus
SRCB =									\
		$(SRCB_PATH)/main_bonus.c		\
		$(SRCB_PATH)/pipex_bonus.c		\
		$(SRCB_PATH)/utils_bonus.c		\
		$(SRCB_PATH)/file_pipe_bonus.c	\
		$(SRCB_PATH)/exec_bonus.c		\
		$(SRCB_PATH)/heredoc_bonus.c	\
#########################################

## LIBFT #####################

LIBFT = libft.a
LIB_PATH = lib/
LIB = $(LIB_PATH)$(LIBFT)
LIB_LINK = -L $(LIB_PATH) -lft
##############################

OBJ = $(SRC:.c=.o)
BNS = $(SRCB:.c=.o)

all: lib $(NAME)

$(NAME): $(OBJ) $(HDR)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_LINK) -o $(NAME)

bonus: lib $(BNS) $(HDRB)
	$(CC) $(CFLAGS) $(BNS) $(LIB_LINK) -o $(NAME)

lib:
	make -C $(LIB_PATH) $(LIBFT)

libclean:
	make -C $(LIB_PATH) clean

libfclean:
	make -C $(LIB_PATH) fclean

clean: libclean
	rm -rf $(OBJ) $(BNS)
	
fclean: clean libfclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus lib libclean libfclean clean fclean re
	
