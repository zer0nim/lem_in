/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:03:55 by emarin            #+#    #+#             */
/*   Updated: 2018/02/07 11:37:20 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	ft_init_dijkstra(t_anthill *anthill, char reinit)
{
	t_room	*tmp;

	tmp = anthill->room;
	while (tmp)
	{
		if (!(reinit
		&& ((anthill->end)->prev == anthill->start || tmp->found == -1)))
		{
			tmp->dist = -1;
			tmp->found = 0;
			tmp->prev = NULL;
		}
		tmp = tmp->next;
	}
	(anthill->start)->dist = 0;
}

t_room	*smallest_node(t_anthill *anthill)
{
	t_room	*tmp;
	t_room	*min;

	min = NULL;
	tmp = anthill->room;
	while (tmp)
	{
		if (!tmp->found && tmp->dist != -1 && (!min || tmp->dist < min->dist))
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

void	ft_block_short(t_anthill *anthill)
{
	t_room	*tmp;

	tmp = anthill->end;
	while (tmp->prev)
	{
		tmp->found = -1;
		tmp = tmp->prev;
	}
	(anthill->end)->found = 1;
}

void	ft_dijkstra(t_anthill *anthill, char reinit)
{
	t_room	*tmp;
	int		i;

	ft_init_dijkstra(anthill, reinit);
	while ((tmp = smallest_node(anthill)))
	{
		tmp->found = 1;
		i = -1;
		while (tmp->near && tmp->near[++i])
		{
			if (!(tmp->near[i])->found
			&& ((tmp->near[i])->dist > tmp->dist + 1
			|| (tmp->near[i])->dist == -1))
			{
				(tmp->near[i])->dist = tmp->dist + 1;
				(tmp->near[i])->prev = tmp;
			}
		}
	}
}
