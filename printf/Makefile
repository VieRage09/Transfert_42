NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

HDR = libft/libft.a

EXEC = maintest

SRC =			\
	ft_printf.c	\

OBJ = $(SRC:.c=.o) 

$(NAME) : $(OBJ)
			ar rcs $(NAME) $(OBJ)

all : $(NAME)

clean :
			rm -f $(OBJ)

fclean : clean
			rm -f $(NAME)

re : fclean all

test : $(OBJ)
			$(CC) $(CFLAGS) $(SRC) $(HDR) -o $(EXEC)

.PHONY : all clean fclean re test
