# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 15:17:35 by tlebon            #+#    #+#              #
#    Updated: 2025/02/20 15:59:36 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= genclass

#---------------------COMPILATION-----------------------#
CC		= c++
CFLAGS	= -Wall -Werror -Wextra
#-------------------------------------------------------#

#---------------------SOURCES---------------------------#
SRC_PATH	= src/
SRC			= 						\
				main.cpp			\
				utils.cpp			\
				write_cpp.cpp		\
				write_header.cpp	\

SRCS		= $(addprefix $(SRC_PATH), $(SRC))
#-------------------------------------------------------#

#---------------------HEADERS---------------------------#
HDR			=						\
				genclass.hpp		\
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