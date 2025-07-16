# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/02/26 15:39:50 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= animal

CC		= c++ -Wall -Werror -Wextra -std=c++98

SRC		= 					\
			A_Animal.cpp	\
			Brain.cpp		\
			Cat.cpp			\
			Dog.cpp			\
			main.cpp		\

HDR		=					\
			A_Animal.hpp	\
			Brain.hpp		\
			Cat.hpp			\
			Dog.hpp			\

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