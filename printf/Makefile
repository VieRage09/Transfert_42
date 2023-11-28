NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

HDR = libftprintf.h

EXEC = maintest

SRC =					\
		ft_printf.c		\
		ft_print_char.c \
		ft_print_str.c	\
		ft_print_int.c	\

OBJ = $(SRC:.c=.o) 

$(NAME) : $(OBJ)
			ar crs $(NAME) $(OBJ)

all : $(NAME)

clean :
			rm -f $(OBJ)

fclean : clean
			rm -f $(NAME)

re : fclean all

test : $(NAME) lib
			$(CC) $(CFLAGS) test.c $(NAME) libft/libft.a -o $(EXEC)

lib : 
			make -C libft libft.a

.PHONY : all clean fclean re test
