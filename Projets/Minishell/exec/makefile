# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 19:17:15 by tlebon            #+#    #+#              #
#    Updated: 2024/10/13 20:55:38 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#-------------------------------------------------------------- COMPILATION ---#
CC = cc
LFLAGS = -lreadline
CFLAGS = -g -Wall -Werror -Wextra
#------------------------------------------------------------------------------#

#------------------------------------------------------------------- HEADER ---#
HDR_PATH = includes
HDR = $(HDR_PATH)/minishell.h
#------------------------------------------------------------------------------#

#-------------------------------------------------------------------- LIBFT ---#
LIBFT_PATH	= libs/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
#------------------------------------------------------------------------------#

#-------------------------------------------------------------------INCLUDES---#
INC			=	-I ./includes/\
				-I ./libs/libft/\
#------------------------------------------------------------------------------#

#---------------------------------------------------------------------- SRC ---#
SRC_PATH = src
SRC =																		\
		$(SRC_PATH)/bin/bin_utils.c											\
		$(SRC_PATH)/bin/cd.c												\
		$(SRC_PATH)/bin/echo.c												\
		$(SRC_PATH)/bin/env.c												\
		$(SRC_PATH)/bin/exit.c												\
		$(SRC_PATH)/bin/export.c											\
		$(SRC_PATH)/bin/pwd.c												\
		$(SRC_PATH)/bin/unset.c												\
		$(SRC_PATH)/execution/bool.c										\
		$(SRC_PATH)/execution/command.c										\
		$(SRC_PATH)/execution/execute.c										\
		$(SRC_PATH)/execution/in_out_files.c								\
		$(SRC_PATH)/execution/pipe.c										\
		$(SRC_PATH)/execution/utils.c										\
		$(SRC_PATH)/parsing/env_utils.c										\
		$(SRC_PATH)/main.c													\

SRCS = $(addprefix $(SRC_PATH), $(SRC))
#------------------------------------------------------------------------------#


#------------------------------------------------------------------------OBJ---#
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
#------------------------------------------------------------------------------#

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)/bin/%.c $(SRC_PATH)/execution/%.c $(SRC_PATH)/parsing/%.c $SRC_PATH/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	make -sC $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC)

lib:
	make -C $(LIB_PATH)

clean:
	@make fclean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH) 	

fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_PATH) fclean

re : fclean all

.PHONY: all clean fclean re