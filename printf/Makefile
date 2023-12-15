# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 18:04:33 by tlebon            #+#    #+#              #
#    Updated: 2023/12/11 18:57:05 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HDR = ft_printf.h

PATHLIB = ./libft

LIBA = $(PATHLIB)/libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC =					\
	ft_printf.c			\
	ft_print_char.c		\
	ft_print_hex_low.c	\
	ft_print_hex_up.c	\
	ft_print_int.c		\
	ft_print_pointer.c	\
	ft_print_str.c		\
	ft_print_uns_int.c	\

OBJ = $(SRC:.c=.o) 

$(NAME) : $(OBJ)
			make -C $(PATHLIB)
			cp $(LIBA) $(NAME) 
			ar crs $(NAME) $(OBJ)

all : $(NAME)

clean :
			make clean -C $(PATHLIB)
			rm -f $(OBJ)

fclean : clean
			make fclean -C $(PATHLIB)
			rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
