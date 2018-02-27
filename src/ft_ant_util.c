/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ant_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:28:03 by emarin            #+#    #+#             */
/*   Updated: 2018/02/05 19:11:30 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char	init_ant_len(t_anthill *anthill, char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isnb(line[i]))
		++i;
	if (line[0] == '0' || line[i])
		return (0);
	if (((long long)ft_atoi(line) != ft_atoi_l(line)) || i > 11)
		return (0);
	anthill->ant_len = ft_atoi(line);
	if (!(anthill->ant = (t_room **)malloc(sizeof(t_room *)
	* anthill->ant_len + 1)))
		return (0);
	while (i > 0)
	{
		anthill->ant[i] = NULL;
		--i;
	}
	return (1);
}

void	add_room(t_anthill *anthill, t_room *room)
{
	if (!anthill->room)
		anthill->room = room;
	else
	{
		room->next = anthill->room;
		anthill->room = room;
	}
}

char	ft_realcat_near(t_room *a, t_room *b)
{
	t_room	**tmp;
	int		i;

	i = 0;
	if (a->near)
	{
		while ((a->near)[i] && (a->near)[i] != b)
			++i;
		if ((a->near)[i])
			return (1);
		if (!(tmp = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
			return (0);
		i = -1;
		while ((a->near)[++i])
			tmp[i] = (a->near)[i];
		free(a->near);
		a->near = tmp;
	}
	else if (!(a->near = (t_room **)malloc(sizeof(t_room *) * 2)))
		return (0);
	(a->near)[i++] = b;
	(a->near)[i] = NULL;
	return (1);
}

char	ft_set_near(t_room *a, t_room *b)
{
	if (!ft_realcat_near(a, b))
		return (0);
	if (!ft_realcat_near(b, a))
		return (0);
	return (1);
}
