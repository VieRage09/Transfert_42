# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 19:17:15 by tlebon            #+#    #+#              #
#    Updated: 2024/10/10 16:24:44 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#-------------------------------------------------------------- COMPILATION ---#
CC = cc
LFLAGS = -lreadline
CFLAGS = -g -Wall -Werror -Wextra
#------------------------------------------------------------------------------#

#------------------------------------------------------------------- HEADER ---#
HDR_PATH = include
HDR = $(HDR_PATH)/minishell.h
#------------------------------------------------------------------------------#

#---------------------------------------------------------------------- SRC ---#
SRC_PATH = src
SRC =																		\
		$(SRC_PATH)/bin/cd.c												\
		$(SRC_PATH)/bin/pwd.c												\
		$(SRC_PATH)/bin/env.c												\
		$(SRC_PATH)/command.c												\
		$(SRC_PATH)/execute.c												\
		$(SRC_PATH)/in_out_files.c											\
		$(SRC_PATH)/main.c													\
		$(SRC_PATH)/pipe.c													\
		$(SRC_PATH)/utils.c													\
#------------------------------------------------------------------------------#

#-------------------------------------------------------------------- LIBFT ---#
LIB_PATH = include/lib
LIB = $(LIB_PATH)/libft.a
#------------------------------------------------------------------------------#


OBJ = $(SRC:.c=.o)

all: lib $(NAME)

$(NAME): $(OBJ) $(HDR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

lib:
	make -C $(LIB_PATH)

clean:
	rm -rf $(OBJ)
	make -C $(LIB_PATH) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_PATH) fclean

re : fclean all

.PHONY: all clean fclean re