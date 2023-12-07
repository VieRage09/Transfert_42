NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

HDR = libftprintf.h

EXEC = maintest

SRC = $(wildcard *.c)					

SRCL = $(wildcard libft/*.c)

OBJ = $(SRC:.c=.o) 

OBJL = $(SRCL:.c=.o)

$(NAME) : $(OBJL) $(OBJ)
			ar crs $(NAME) $(OBJL) $(OBJ)

all : $(NAME)

li : 
			make -C libft

test : comp 
			./test
comp : 
			cc tests.c -o $(EXEC) libftprintf.a

clean :
			rm -f $(OBJ) $(OBJL)

fclean : clean
			rm -f $(NAME)
			rm $(EXEC)

re : fclean all

.PHONY : all clean fclean re
