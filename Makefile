# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emarin <emarin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 11:20:07 by emarin            #+#    #+#              #
#    Updated: 2018/02/21 11:27:30 by emarin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARG = test_map/visu/my.map

NAME1 = lem-in

SRC_NAME1 = ft_lem_in.c \
			parse_ant.c \
			ft_util.c \
			ft_ant_util.c \
			ft_dijkstra.c \
			ft_dijkstra_util.c \
			ft_print_res.c \
			ft_map.c \
			ft_bonus.c

SRC_PATH = src

OBJ_PATH = obj

OBJ_NAME1 = $(SRC_NAME1:.c=.o)

SRC1 = $(addprefix $(SRC_PATH)/,$(SRC_NAME1))

OBJ1 = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME1))

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libftprintf.a

VISU = lem_in_visu/lem_in_visu

HEADERS = -I ./

all: $(NAME1)

$(LIBFT) : |
	@MAKE -C libft

$(NAME1): $(LIBFT) $(OBJ1)
	gcc -o $(NAME1) $(OBJ1) $(LIBFT)
	@MAKE -C lem_in_visu

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c lem_in.h
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc -c $(FLAGS) -o $@ -c $<

clean:
	make -C libft/ clean
	rm -f $(OBJ1)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make -C lem_in_visu/ fclean
	make -C libft/ fclean
	rm -f $(NAME1)

re: fclean all

test: all
	@MAKE -C lem_in_visu test

.PHONY: all, clean, fclean, re
