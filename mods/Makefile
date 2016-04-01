NAME = libmods.a
SRC = $(shell find ./src -name '*\.c')
OBJ = $(subst .c,.o, $(SRC))

HEADDIR	?= $(PWD)/inc
CC		?= clang
CFLAGS	?= -I$(HEADDIR) -Wall -Werror -Wextra -g3

all: $(NAME) test

test: libmods.a
	$(CC) $(CFLAGS) -lmods -L. -o test test.c

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

clean:
	rm -rf test
	rm -rf $(OBJ)

fclean:
	rm -rf test
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all
