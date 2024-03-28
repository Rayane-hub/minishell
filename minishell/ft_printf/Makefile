CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c ft_print_u.c ft_putchar.c ft_putnbr_base.c ft_putnbr.c ft_putstr.c

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

.PHONY : all bonus clean fclean re

all : $(NAME)

%.o : %.c ft_printf.h
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) 
		ar rcs $(NAME) $(OBJ)

clean :
		rm -rf  $(OBJ)

fclean : clean
		rm -f $(NAME)

re : fclean all