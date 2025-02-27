# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:26:44 by tlebon            #+#    #+#              #
#    Updated: 2025/02/27 21:14:48 by tlebon           ###   ########.fr        #
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
	@make --silent folie

%.o: %.cpp $(HDR)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

folie:
	@echo "                    (        (          "
	@echo "    (          (    )\\ )     )\\(    (   "
	@echo "    )\\  (     ))\\  (())/\\  ( ((_)\  ))\\  "
	@echo " _ ((_) )\\ ) /((_)  /(_)) )\\ _((_)/((_) "
	@echo "| | | |_(_/((_))   (_) _|((_) |(_|_))   "
	@echo "| |_| | ' \\)) -_)   |  _/ _ \\ || / -_)  "
	@echo " \\___/|_||_|\\___|   |_| \\___/_||_\\___|  "

re: fclean all

.PHONY: clean fclean re

