/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:04:47 by emarin            #+#    #+#             */
/*   Updated: 2018/02/02 16:33:54 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char	is_equal(char *name, char *line, char separator)
{
	int	i;

	i = 0;
	while (line[i] && name[i] && line[i] == name[i])
		++i;
	return (!name[i] && (!line[i] || line[i] == separator));
}

char	verif_room(t_anthill *anthill, char *line, int *name)
{
	t_room	*tmp;
	int		i;

	i = 0;
	if (line[0] == 'L')
		return (0);
	while (line[i] && line[i] != ' ')
		++i;
	*name = i;
	++i;
	while (line[i] && ft_isnb(line[i]))
		++i;
	if (!line[i] || line[i] != ' ')
		return (0);
	++i;
	while (line[i] && ft_isnb(line[i]))
		++i;
	if (line[i])
		return (0);
	tmp = anthill->room;
	while (tmp && !is_equal(tmp->name, line, ' '))
		tmp = tmp->next;
	if (tmp)
		return (0);
	return (1);
}

char	init_room(t_anthill *anthill, char *line)
{
	t_room	*room;
	int		i;
	int		name;

	if (!verif_room(anthill, line, &name)
	|| (!(room = (t_room *)malloc(sizeof(t_room)))
	|| !(room->name = (char *)malloc(sizeof(char) * name + 1))))
		return (0);
	i = -1;
	while (line[++i] && line[i] != ' ')
		(room->name)[i] = line[i];
	(room->name)[i] = '\0';
	++i;
	if (!ft_overflow(line + i))
		return (0);
	room->x = ft_atoi(line + i);
	while (line[i] && ft_isnb(line[i]))
		++i;
	if (!ft_overflow(line + i))
		return (0);
	room->y = ft_atoi(line + i + 1);
	room->next = NULL;
	room->near = NULL;
	add_room(anthill, room);
	return (1);
}

char	init_pipe(t_anthill *anthill, char *line)
{
	int		i;
	t_room	*a;
	t_room	*b;

	a = anthill->room;
	while (a && !is_equal(a->name, line, '-'))
		a = a->next;
	if (!a)
		return (0);
	i = 0;
	while (line[i] && line[i] != '-')
		++i;
	if (!line[i])
		return (0);
	b = anthill->room;
	while (b && !is_equal(b->name, line + i + 1, '-'))
		b = b->next;
	if (!b)
		return (0);
	if (!ft_set_near(a, b))
		return (0);
	return (1);
}

char	ft_parse_ant(t_anthill *anthill, char *line, char *state)
{
	if (line[0] == '#')
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			*state = (!ft_strcmp(line, "##start")) ? 2 : 3;
	}
	else if (!anthill->ant)
	{
		if (!init_ant_len(anthill, line))
			return (0);
	}
	else
	{
		if (!ft_strchr(line, '-'))
		{
			if (!init_room(anthill, line))
				return (0);
			if (*state == 2 || *state == 3)
				*state += 2;
		}
		else if (!init_pipe(anthill, line))
			return (0);
	}
	return (1);
}
