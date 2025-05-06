# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lberne <lberne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 15:45:33 by tlebon            #+#    #+#              #
#    Updated: 2025/05/06 14:58:34 by lberne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D 

#---------------------COMPILATION-----------------------#
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
#-------------------------------------------------------#

#---------------------SOURCES---------------------------#
SRC_PATH	=	src/
SRC			=								\
                main.c						\
                parsing/check_map.c			\
                parsing/check_rgb.c			\
                parsing/clean_up.c			\
                parsing/errors.c			\
                parsing/init_map_struct.c	\
                parsing/init_map_tab.c		\
                parsing/init_other.c		\
                parsing/utils_1.c			\
                parsing/utils_2.c			\
                execution/draw_frame.c		\
                execution/game_loop.c		\
                execution/mlx_utils.c		\
                execution/player_move.c		\
                execution/draw_line.c		\

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
#-------------------------------------------------------#

#---------------------LIBS------------------------------#
LIBS_PATH	=	libs/

LIBFT_NAME	=	libft.a
LIBFT_PATH	=	$(LIBS_PATH)libft/
LIBFT		=	$(LIBFT_PATH)$(LIBFT_NAME)

MLX_NAME	=	$(MLX_PATH)libmlx.a
MLX_PATH	=	$(LIBS_PATH)minilibx/
MLX_LINK	=	-L $(MLX_PATH) -lmlx -lXext -lX11 -lm
#-------------------------------------------------------#

#---------------------HEADERS---------------------------#
HDR_PATH	=	include/
HDR			=	$(HDR_PATH)cub3D.h

INC			=	-I include/\
                -I $(LIBFT_PATH)includes/\
                -I /opt/X11/include/
#-------------------------------------------------------#

#---------------------OBJETS----------------------------#
OBJ_PATH	=	obj/
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
#-------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_NAME)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_LINK) $(INC)
	@make --silent folie

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(MLX_NAME):
	@make -sC $(MLX_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HDR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@make --silent sweep
	@rm -rf $(OBJ_PATH)
	@make -sC $(LIBFT_PATH) fclean
	@make -sC $(MLX_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -sC $(LIBFT_PATH) fclean
	@make -sC $(MLX_PATH) clean

re: fclean all 



# Define color codes
BLUE	= \033[94m
RED		= \033[95;52m
RESET	= \033[0m

folie:
	@printf "$(RED)_________                        ___________      __________                                    ________     __________      \n"
	@printf "$(RED)__  ____/____________ ______________(_)__  /_____ __  /___(_)____________     ____________      ___  __/________  /__(_)____ \n"
	@printf "$(RED)_  /    _  __ \\_  __ \`__ \\__  __ \\_  /__  /_  __ \`/  __/_  /_  __ \\_  __ \\    _  _ \\_  __ \\     __  /_ _  __ \\_  /__  /_  _ \\ \n"
	@printf "$(RED)/ /___  / /_/ /  / / / / /_  /_/ /  / _  / / /_/ // /_ _  / / /_/ /  / / /    /  __/  / / /     _  __/ / /_/ /  / _  / /  __/ \n"
	@printf "$(RED)\\____/  \\____//_/ /_/ /_/_  .___//_/  /_/  \\__,_/ \\__/ /_/  \\____//_/ /_/     \\___//_/ /_/      /_/    \\____//_/  /_/  \\___/  \n"
	@printf "$(RED)                         /_/                                                                                                  $(RESET)\n"

sweep:
	@printf "${BLUE}           ______           __  __                                                          \n"
	@printf "          / ____/__  ____  / /_/ /__  ____ ___  ____ _____     ______      _____  ___  ____ \n"
	@printf "         / / __/ _ \/ __ \/ __/ / _ \/ __ \`__ \/ __ \`/_ __ \  / ___/ | /| / / _ \/ _ \/ __ \\ \n"
	@printf "        / /_/ /  __/ / / / /_/ /  __/ / / / / / /_/ / / / /  (__  )| |/ |/ /  __/  __/ /_/ / \n"
	@printf "        \\____/\\___/_/ /_/\\__/_/\\___/_/ /_/ /_/\\__,_/ / /_/  /____/ |__/|__/\\___/\\___/ .___/ \n"
	@printf "                                                                                   /_/       ${RESET}\n"


.PHONY: mlx libft clean fclean re folie sweep