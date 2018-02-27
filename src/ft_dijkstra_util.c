/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:37:11 by emarin            #+#    #+#             */
/*   Updated: 2018/02/09 12:29:24 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	**ft_realcat_end_prev(t_room **end_prev, t_room *new_prev)
{
	t_room	**tmp;
	int		i;

	i = 0;
	if (end_prev)
	{
		while (end_prev[i])
			++i;
		if (!(tmp = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
			return (NULL);
		i = -1;
		while (end_prev[++i])
			tmp[i] = end_prev[i];
		free(end_prev);
		end_prev = tmp;
	}
	else if (!(end_prev = (t_room **)malloc(sizeof(t_room *) * 2)))
		return (NULL);
	end_prev[i++] = new_prev;
	end_prev[i] = NULL;
	return (end_prev);
}

char	ft_check_alrdy_print(t_room *crnt, t_room *near, t_room *room, int pos)
{
	char	already_printed;
	t_room	*tmp;
	int		j;
	int		k;

	already_printed = 0;
	j = -1;
	tmp = room;
	while (++j < pos)
	{
		if (tmp == near)
		{
			k = 0;
			while (tmp->near && (tmp->near)[k] && (tmp->near)[k] != crnt)
				++k;
			if (tmp->near && (tmp->near)[k] && (tmp->near)[k] == crnt)
				already_printed = 1;
		}
		tmp = tmp->next;
	}
	return (already_printed);
}

void	ft_print_near(t_room *crnt, t_room **near, t_room *room, int pos)
{
	char	already_printed;
	int		i;

	i = -1;
	while (near[++i])
	{
		already_printed = ft_check_alrdy_print(crnt, near[i], room, pos);
		if (!already_printed)
			ft_printf("%s-%s\n", crnt->name, (near[i])->name);
	}
}

int		*ft_get_path_len(t_room **end_prev)
{
	int		*res;
	int		i;
	int		len;
	t_room	*tmp;

	i = 0;
	while (end_prev[i])
		++i;
	if (!(res = (int *)malloc(sizeof(int) * i + 1)))
		return (NULL);
	res[i] = -1;
	i = -1;
	while (end_prev[++i])
	{
		len = 1;
		tmp = end_prev[i];
		while (tmp->prev)
		{
			++len;
			tmp = tmp->prev;
		}
		res[i] = len;
	}
	return (res);
}

void	ft_add_next_path(t_anthill *anthill, t_room **end_prev)
{
	int		i;
	t_room	*tmp;
	t_room	*past;

	i = -1;
	while (end_prev[++i])
	{
		tmp = end_prev[i];
		past = anthill->end;
		while (tmp)
		{
			tmp->next_p = past;
			if (!tmp->prev)
				end_prev[i] = past;
			past = tmp;
			tmp = tmp->prev;
		}
	}
	(anthill->end)->next_p = NULL;
}
