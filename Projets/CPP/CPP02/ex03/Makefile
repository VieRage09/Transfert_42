# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/02/05 18:46:28 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fixed_upgrade

CC		= c++ -Wall -Werror -Wextra -std=c++98

SRC		= 					\
			main.cpp		\
			Point.cpp		\
			Fixed.cpp		\
			bsp.cpp			\

HDR		=					\
			Fixed.hpp		\
			Point.hpp		\

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

re: fclean all

.PHONY: clean fclean re