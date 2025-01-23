# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 15:17:35 by tlebon            #+#    #+#              #
#    Updated: 2025/01/23 17:25:00 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= phonebook

#---------------------COMPILATION-----------------------#
CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
#-------------------------------------------------------#

#---------------------SOURCES---------------------------#
SRC_PATH	= src/
SRC			= 					\
				main.cpp		\
				Contact.cpp		\
				PhoneBook.cpp	\

SRCS		= $(addprefix $(SRC_PATH), $(SRC))
#-------------------------------------------------------#

#---------------------HEADERS---------------------------#
HDR_PATH	= include/
HDR			=									\
				$(HDR_PATH)crappy.hpp			\
				$(HDR_PATH)Contact.hpp			\
				$(HDR_PATH)PhoneBook.hpp		\
#-------------------------------------------------------#

#---------------------OBJETS----------------------------#
OBJ_PATH	= obj/
OBJ			= $(SRC:.cpp=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
#-------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(HDR)
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@
clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re