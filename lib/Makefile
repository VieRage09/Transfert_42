# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 17:36:09 by tlebon            #+#    #+#              #
#    Updated: 2024/05/30 19:58:21 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

## COMPILATION ###############

CC = cc
CFLAGS = -Wall -Werror -Wextra
##############################

## HEADERS ##############################################

INCLUDES_PATH = includes
HDR =										\
		$(INCLUDES_PATH)/libft.h			\
		$(INCLUDES_PATH)/get_next_line.h	\
		$(INCLUDES_PATH)/ft_printf.h		\
#########################################################

## SRC ######################################

SRC_PATH = src
SRC =									\
		$(SRC_PATH)/ft_atof.c			\
		$(SRC_PATH)/ft_atoi.c			\
		$(SRC_PATH)/ft_atol.c			\
		$(SRC_PATH)/ft_bzero.c			\
		$(SRC_PATH)/ft_calloc.c			\
		$(SRC_PATH)/ft_free_tab.c		\
		$(SRC_PATH)/ft_isalnum.c		\
		$(SRC_PATH)/ft_isalpha.c		\
		$(SRC_PATH)/ft_isascii.c		\
		$(SRC_PATH)/ft_isdigit.c		\
		$(SRC_PATH)/ft_isprint.c		\
		$(SRC_PATH)/ft_isspace.c		\
		$(SRC_PATH)/ft_itoa.c			\
		$(SRC_PATH)/ft_memchr.c			\
		$(SRC_PATH)/ft_memcmp.c			\
		$(SRC_PATH)/ft_memcpy.c			\
		$(SRC_PATH)/ft_memmove.c		\
		$(SRC_PATH)/ft_memset.c			\
		$(SRC_PATH)/ft_print_str_tab.c	\
		$(SRC_PATH)/ft_putchar_fd.c		\
		$(SRC_PATH)/ft_putchar.c		\
		$(SRC_PATH)/ft_putendl_fd.c		\
		$(SRC_PATH)/ft_putnbr_fd.c		\
		$(SRC_PATH)/ft_putstr_fd.c		\
		$(SRC_PATH)/ft_putstr.c			\
		$(SRC_PATH)/ft_split.c			\
		$(SRC_PATH)/ft_str_is_wspace.c	\
		$(SRC_PATH)/ft_strchr.c			\
		$(SRC_PATH)/ft_strdup.c			\
		$(SRC_PATH)/ft_striteri.c		\
		$(SRC_PATH)/ft_strjoin.c		\
		$(SRC_PATH)/ft_strlcat.c		\
		$(SRC_PATH)/ft_strlcpy.c		\
		$(SRC_PATH)/ft_strlen.c			\
		$(SRC_PATH)/ft_strmapi.c		\
		$(SRC_PATH)/ft_strncmp.c		\
		$(SRC_PATH)/ft_strnstr.c		\
		$(SRC_PATH)/ft_strrchr.c		\
		$(SRC_PATH)/ft_strtrim.c		\
		$(SRC_PATH)/ft_substr.c			\
		$(SRC_PATH)/ft_tolower.c		\
		$(SRC_PATH)/ft_toupper.c		\
		$(SRC_PATH)/get_next_line/get_next_line.c		\
		$(SRC_PATH)/get_next_line/get_next_line_utils.c	\
		$(SRC_PATH)/get_next_line/get_next_line_bonus.c	\
		$(SRC_PATH)/printf/ft_printf.c			\
		$(SRC_PATH)/printf/ft_print_char.c		\
		$(SRC_PATH)/printf/ft_print_hex_low.c	\
		$(SRC_PATH)/printf/ft_print_hex_up.c	\
		$(SRC_PATH)/printf/ft_print_int.c		\
		$(SRC_PATH)/printf/ft_print_pointer.c	\
		$(SRC_PATH)/printf/ft_print_str.c		\
		$(SRC_PATH)/printf/ft_print_uns_int.c	\

SRCB =									\
		$(SRC_PATH)/ft_lstnew.c			\
		$(SRC_PATH)/ft_lstadd_front.c	\
		$(SRC_PATH)/ft_lstsize.c		\
		$(SRC_PATH)/ft_lstlast.c		\
		$(SRC_PATH)/ft_lstadd_back.c	\
		$(SRC_PATH)/ft_lstdelone.c		\
		$(SRC_PATH)/ft_lstclear.c		\
		$(SRC_PATH)/ft_lstiter.c		\
		$(SRC_PATH)/ft_lstmap.c			\
#############################################

OBJ = $(SRC:.c=.o)
BNS = $(SRCB:.c=.o)

$(NAME) : $(OBJ) $(BNS) $(HDR)
	ar crs $(NAME) $(OBJ) $(BNS)

all: $(NAME)

#bonus: $(BNS) $(HDR)
#	ar crs $(NAME) $(BNS)

clean:
	rm -rf $(OBJ) $(BNS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re so
