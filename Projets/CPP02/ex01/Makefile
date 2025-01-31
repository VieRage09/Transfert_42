# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/01/31 21:02:40 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fixed_upgrade

CC		= c++ -Wall -Werror -Wextra -std=c++98

SRC		= 					\
			main.cpp		\
			Fixed.cpp		\

HDR		=	Fixed.hpp

OBJ		= $(SRC:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(HDR)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.cpp $(HDR)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf *.replace

re: fclean all

.PHONY: clean fclean re