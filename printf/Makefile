# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/23 04:54:36 by adebray           #+#    #+#              #
#    Updated: 2016/02/19 14:15:38 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
HEADDIR = ../inc

SRC =	ft_atoi.c \
		ft_isdigit.c \
		ft_itoa.c \
		ft_printf.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_strlen.c \
		ft_octal.c \
		ft_hexa.c \
		ft_sheum_hexa.c \
		tools.c

OBJ = $(subst .c,.o,$(SRC))

CC ?= gcc
CFLAGS ?= -Werror -Wall -Wextra -Wuninitialized -O3
HEADFLAG = -I $(HEADDIR)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(CCFLAGS) $(HEADFLAG) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
