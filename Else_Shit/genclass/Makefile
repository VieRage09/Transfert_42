# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/02/19 20:54:13 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= genclass

CC		= c++ -Wall -Werror -Wextra -std=c++98

SRC		= 						\
			utils.cpp			\
			write_cpp.cpp		\
			write_header.cpp	\
			main.cpp			\

HDR		=					\
			genclass.hpp	\

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