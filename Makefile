NAME	= libftprintf.a
CC	= cc
CFLAGS	= -Wall -Wextra -Werror

SRC	= chars_printer.c digits_printer.c ft_printf.c hex_printer.c

OBJ	= $(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
