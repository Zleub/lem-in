NAME = lem-in

SRC = $(shell find ./src -name '*.c')
OBJ = $(subst .c,.o, $(SRC))

CC = clang
CFLAGS = -Wall -Werror -Wextra -I inc
LDFLAGS = -L c-libs/ft_printf -l ftprintf -L c-libs/libft -l ft

all: libft ft_printf $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

ft_printf:
	make -C c-libs/ft_printf

libft:
	make -C c-libs/libft

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

.PHONY: ft_printf all clean fclean re libft
