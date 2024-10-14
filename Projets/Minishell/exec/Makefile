# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 19:17:15 by tlebon            #+#    #+#              #
#    Updated: 2024/10/14 20:07:31 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#-------------------------------------------------------------- COMPILATION ---#
CC = cc
LFLAGS = -lreadline
CFLAGS = -g -Wall -Werror -Wextra
#------------------------------------------------------------------------------#

#-------------------------------------------------------------------- LIBFT ---#
LIBFT_PATH	= libs/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
#------------------------------------------------------------------------------#

#-------------------------------------------------------------------INCLUDES---#
INC			=	-I ./includes/\
				-I ./libs/libft/includes\
#------------------------------------------------------------------------------#

#---------------------------------------------------------------------- SRC ---#
SRC_PATH = srcs/

BIN_PATH = bin/
EXEC_PATH = execution/
PARS_PATH = parsing/

SRC =																		\
		$(BIN_PATH)bin_utils.c												\
		$(BIN_PATH)cd.c														\
		$(BIN_PATH)echo.c													\
		$(BIN_PATH)env.c													\
		$(BIN_PATH)exit.c													\
		$(BIN_PATH)export.c													\
		$(BIN_PATH)pwd.c													\
		$(BIN_PATH)unset.c													\
		$(EXEC_PATH)bool.c													\
		$(EXEC_PATH)command.c												\
		$(EXEC_PATH)execute.c												\
		$(EXEC_PATH)in_out_files.c											\
		$(EXEC_PATH)pipe.c													\
		$(EXEC_PATH)utils.c													\
		$(PARS_PATH)env_utils.c												\
		main.c																\

SRCS		= $(addprefix $(SRC_PATH), $(SRC))
#------------------------------------------------------------------------------#


#------------------------------------------------------------------------OBJ---#
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
OBJ_PATH	= obj/
#------------------------------------------------------------------------------#


#------------------------------------------------------------------------HDR---#
HDR			=	includes/minishell.h										\
#------------------------------------------------------------------------------#

vpath %.c $(SRC_PATH) $(SRC_PATH)(BIN_PATH) $(SRC_PATH)$(EXEC_PATH) $(SRC_PATH)$(PARS_PATH)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS) $(LIBFT) $(INC)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HDR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -rf $(OBJ_PATH) 	

fclean: clean
	make -C $(LIBFT_PATH) fclean  
	rm -rf $(NAME)

re : fclean all

.PHONY: all lib clean fclean re