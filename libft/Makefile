# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emarin <emarin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 13:32:09 by emarin            #+#    #+#              #
#    Updated: 2018/01/11 13:29:14 by emarin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_NAME = ft_printf.c \
			type_1.c \
			type_2.c \
			type_3.c \
			type_4.c \
			store_next_par.c \
			ft_unicode.c \
			nbzer.c \
			ft_nb.c \
			ft_nb2.c \
			trn.c

SRC_PATH = src

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

HEADERS = -I ./

all: $(NAME)

$(LIBFT) : |
	@MAKE -C libft

$(NAME): $(LIBFT) $(OBJ)
	cp $(LIBFT) $(NAME)
	ar r $(NAME) $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c ft_printf.h
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc -c $(FLAGS) -o $@ -c $<

clean:
	make -C libft/ clean
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
