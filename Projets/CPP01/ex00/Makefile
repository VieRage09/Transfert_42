# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/01/28 19:55:01 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= zzz

CC		= c++ -Wall -Werror -Wextra -std=c++98

SRC		= 					\
			main.cpp		\
			Zombie.cpp		\
			randomChump.cpp	\
			newZombie.cpp	\

HDR		=	Zombie.hpp

OBJ		= $(SRC:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(HDR)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re