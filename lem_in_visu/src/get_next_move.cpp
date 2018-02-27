/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_move.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 10:45:17 by emarin            #+#    #+#             */
/*   Updated: 2018/02/21 10:35:51 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_visu.h"
# include "../include/ant.h"

extern int STEP;

t_room	*find_room(char *line, t_anthill *anthill)
{
	t_room *room;

	room = anthill->room;
	while (room && ft_memcmp(line, room->name, ft_strlen(room->name)))
		room = room->next;
	return (room);
}

int		get_next_move(std::vector<Ant> *ants, t_anthill *anthill)
{
	int			ret;
	char		*line;
	char		*cop_line;
	t_room		*room;
	int			index = 0;

// printf("\nnext_move\n");
	if ((ret = ft_get_next_line(STDIN_FILENO, &line)))
	{
		cop_line = line + 1;
		while (*cop_line)
		{
			index = ft_atoi(cop_line) - 1;
			while (*cop_line && ft_isnb(*cop_line))
				++cop_line;
			if (*cop_line)
				++cop_line;
			room = find_room(cop_line, anthill);

// printf("dest_x=%d, dest_y=%d\n", room->x * UNIT_SIZE + ROOM_SIZE / 2, room->y * UNIT_SIZE + ROOM_SIZE / 2);
			(*ants)[index].setDest(room->x * UNIT_SIZE + ROOM_SIZE / 2
												 , room->y * UNIT_SIZE + ROOM_SIZE / 2);
			while (*cop_line && *cop_line != ' ')
				++cop_line;

			if (*cop_line)
				cop_line += 2;
		}
		// L8-room0 L9-room0 L10-room6
		++STEP;
	}
	free(line);
	return (ret);
}
