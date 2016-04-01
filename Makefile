# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/19 13:15:58 by adebray           #+#    #+#              #
#    Updated: 2016/04/01 17:53:06 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/lem-in
SRC = $(shell find ./src -name '*\.c')
SRC += main.c
OBJ = $(subst .c,.o, $(SRC))

export HEADDIR = $(PWD)/inc
export CC = clang
export CFLAGS = -I$(HEADDIR) -Wall -Werror -Wextra -g3

LDLIBS = -Llibft -lft -Lprintf -lftprintf

all: libft printf $(NAME)

$(NAME): $(OBJ)
	mkdir -p bin
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

libft:
	make -C libft

printf:
	make -C printf

re:
	make fclean
	make all

clean:
	make -C libft clean
	make -C printf clean
	rm -rf $(OBJ)

fclean:
	make -C libft fclean
	make -C printf fclean
	rm -rf $(OBJ)
	rm -rf $(NAME)

.PHONY: all $(NAME) re clean fclean libft printf
