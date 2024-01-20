# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 17:36:09 by tlebon            #+#    #+#              #
#    Updated: 2023/12/11 18:01:29 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC =				\
		ft_calloc.c	\
		ft_isascii.c	\
		ft_itoa.c	\
		ft_memcpy.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_strdup.c	\
		ft_strlcat.c	\
		ft_strmapi.c	\
		ft_strrchr.c	\
		ft_tolower.c	\
		ft_atoi.c	\
		ft_isalnum.c	\
		ft_isdigit.c	\
		ft_memchr.c	\
		ft_memmove.c	\
		ft_putendl_fd.c	\
		ft_split.c	\
		ft_striteri.c	\
		ft_strlcpy.c	\
		ft_strncmp.c	\
		ft_strtrim.c	\
		ft_toupper.c	\
		ft_bzero.c	\
		ft_isalpha.c	\
		ft_isprint.c	\
		ft_memcmp.c	\
		ft_memset.c	\
		ft_putnbr_fd.c	\
		ft_strchr.c	\
		ft_strjoin.c	\
		ft_strlen.c	\
		ft_strnstr.c	\
		ft_substr.c	\

SRCB =					\
		ft_lstnew.c	\
		ft_lstadd_front.c	\
		ft_lstsize.c	\
		ft_lstlast.c	\
		ft_lstadd_back.c	\
		ft_lstdelone.c	\
		ft_lstclear.c	\
		ft_lstiter.c	\
		ft_lstmap.c	\

HDR = libft.h

OBJ = $(SRC:.c=.o)

BNS = $(SRCB:.c=.o)

$(NAME) : $(OBJ)
	ar crs $(NAME) $(OBJ)

all: $(NAME)

bonus: $(BNS)
	ar crs $(NAME) $(BNS)

clean:
	rm -rf $(OBJ) $(BNS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re so
