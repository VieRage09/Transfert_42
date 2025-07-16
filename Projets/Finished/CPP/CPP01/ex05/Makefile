# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/01/29 21:41:26 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= harl_nous_fais_tous_chier_mais_il_se_bat

CC		= c++ -Wall -Werror -Wextra -std=c++98

SRC		= 					\
			main.cpp		\
			Harl.cpp		\

HDR		=	Harl.hpp	

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