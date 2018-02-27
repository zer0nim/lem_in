# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emarin <emarin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 14:34:48 by emarin            #+#    #+#              #
#    Updated: 2018/02/21 11:32:10 by emarin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARG = ../test_map/visu/my.map

NAME1 = lem-in-visu

SRC_NAME1 = main.cpp \
			ltexture.cpp \
			lem_in_visu.cpp \
			room.cpp \
			road.cpp \
			camera.cpp \
			ant.cpp \
			get_next_move.cpp \
			lwindow.cpp

OBJ2 = ../obj/parse_ant.o \
			../obj/ft_util.o \
			../obj/ft_ant_util.o \
			../obj/ft_dijkstra.o \
			../obj/ft_dijkstra_util.o \
			../obj/ft_print_res.o \
			../obj/ft_map.o \
			../obj/ft_bonus.o

HEADER = lem_in_visu.h \
			include/ltexture.h \
			include/room.h \
			include/road.h \
			include/camera.h \
			include/ant.h

SRC_PATH = src

OBJ_PATH = obj

OBJ_NAME1 = $(SRC_NAME1:.cpp=.o)

SRC1 = $(addprefix $(SRC_PATH)/,$(SRC_NAME1))

OBJ1 = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME1))

SDL = -I include -L lib -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0 -l SDL2_gfx-1.0.0

# FLAGS = -Wall -Wextra -Werror

LIBFT = ../libft/libftprintf.a

all: $(NAME1)

$(NAME1): $(OBJ1) $(OBJ2)
	g++ -o $(NAME1) $(OBJ1) $(OBJ2) $(LIBFT) $(SDL)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	g++ -c $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ1)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	rm -f $(NAME1)

re: fclean all

test: $(NAME1)
	.././lem-in < $(ARG) | ./$(NAME1)

.PHONY: all, clean, fclean, re
