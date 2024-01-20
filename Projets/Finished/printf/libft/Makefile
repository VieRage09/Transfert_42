# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 17:36:09 by tlebon            #+#    #+#              #
#    Updated: 2023/12/06 18:08:16 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = $(wildcard *.c)

HDR = libft.h

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	ar crs $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -rf $(OBJ) $(BNS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 
