# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/02/18 19:49:40 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= clapTrap

CC		= c++ -Wall -Werror -Wextra -std=c++98 -Wno-shadow

SRC		= 					\
			ClapTrap.cpp	\
			ScavTrap.cpp	\
			main.cpp		\

HDR		=					\
			ClapTrap.hpp	\
			ScavTrap.hpp	\

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