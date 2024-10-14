# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 17:36:09 by tlebon            #+#    #+#              #
#    Updated: 2024/10/14 18:52:51 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

#-------------------------------------------------------------- COMPILATION ---#
CC 		= cc
CFLAGS	= -Wall -Werror -Wextra
#------------------------------------------------------------------------------#

#-------------------------------------------------------------------INCLUDES---#
INC_PATH	= ./includes
INC			= -I $(INC_PATH)
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------SRC---#
SRC_PATH	= srcs/
GNL_PATH	= get_next_line/
PRINTF_PATH	= printf/

SRC			=																\
		ft_atof.c															\
		ft_atoi.c															\
		ft_atol.c															\
		ft_bzero.c															\
		ft_calloc.c															\
		ft_dtoa.c															\
		ft_free_tab.c														\
		ft_isalnum.c														\
		ft_isalpha.c														\
		ft_isascii.c														\
		ft_isdigit.c														\
		ft_isprint.c														\
		ft_isspace.c														\
		ft_itoa.c															\
		ft_memchr.c															\
		ft_memcmp.c															\
		ft_memcpy.c															\
		ft_memmove.c														\
		ft_memset.c															\
		ft_print_str_tab.c													\
		ft_putchar_fd.c														\
		ft_putchar.c														\
		ft_putendl_fd.c														\
		ft_putnbr_fd.c														\
		ft_putstr_fd.c														\
		ft_putstr.c															\
		ft_split.c															\
		ft_str_is_wspace.c													\
		ft_strchr.c															\
		ft_strdup.c															\
		ft_striteri.c														\
		ft_strjoin.c														\
		ft_strlcat.c														\
		ft_strlcpy.c														\
		ft_strlen.c															\
		ft_strmapi.c														\
		ft_strncmp.c														\
		ft_strnstr.c														\
		ft_strrchr.c														\
		ft_strtrim.c														\
		ft_substr.c															\
		ft_tolower.c														\
		ft_toupper.c														\
		ft_lstnew.c															\
		ft_lstadd_front.c													\
		ft_lstsize.c														\
		ft_lstlast.c														\
		ft_lstadd_back.c													\
		ft_lstdelone.c														\
		ft_lstclear.c														\
		ft_lstiter.c														\
		ft_lstmap.c															\
		$(GNL_PATH)get_next_line.c											\
		$(GNL_PATH)get_next_line_utils.c									\
		$(GNL_PATH)get_next_line_bonus.c									\
		$(PRINTF_PATH)ft_printf.c											\
		$(PRINTF_PATH)ft_print_char.c										\
		$(PRINTF_PATH)ft_print_hex_low.c									\
		$(PRINTF_PATH)ft_print_hex_up.c										\
		$(PRINTF_PATH)ft_print_int.c										\
		$(PRINTF_PATH)ft_print_pointer.c									\
		$(PRINTF_PATH)ft_print_str.c										\
		$(PRINTF_PATH)ft_print_uns_int.c									\

SRCS		= $(addprefix($(SRC_PATH), $(SRC)))
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------HDR---#
HDR		= 	$(INC_PATH)libft.h												\
			$(INC_PATH)get_next_line.h										\
			$(INC_PATH)ft_printf.h											\
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------OBJ---#
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
#------------------------------------------------------------------------------#


all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	mkdir $@
	mkdir $@$(GNL_PATH)
	mkdir $@$(PRINTF_PATH)

$(NAME) : $(OBJS)
	ar crs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS) $(BNS)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
