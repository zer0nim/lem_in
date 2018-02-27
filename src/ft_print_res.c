/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_res.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:08:01 by emarin            #+#    #+#             */
/*   Updated: 2018/02/21 14:09:33 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char	ft_is_empty(t_anthill *anthill, t_room *room)
{
	int	i;

	i = 0;
	while ((anthill->ant)[i] && (anthill->ant)[i] != room)
		++i;
	return (!(anthill->ant)[i] || (anthill->ant)[i] == anthill->end);
}

void	ft_push_ant(t_anthill *anthill, t_room **end_prev, int *len, char first)
{
	int	i;
	int	j;

	i = 0;
	while (i < anthill->ant_len)
	{
		if ((anthill->ant)[i] == anthill->start)
		{
			j = 0;
			while (end_prev[j]
			&& !ft_is_empty(anthill, end_prev[j])
			&& (len[j] - len[0]) <= (anthill->ant_len - (i + 1)))
				++j;
			if (end_prev[j] && ft_is_empty(anthill, end_prev[j]))
			{
				(anthill->ant)[i] = end_prev[j];
				ft_printf("%s%d-%s"
				, (!first) ? " L" : "L", i + 1, ((anthill->ant)[i])->name);
				first = 0;
			}
		}
		++i;
	}
}

char	ft_print_move(t_anthill *anthill, t_room **end_prev)
{
	int		*len;
	int		i;
	char	first;

	if (!(len = ft_get_path_len(end_prev)))
		return (0);
	ft_add_next_path(anthill, end_prev);
	while ((anthill->ant)[anthill->ant_len - 1] != anthill->end)
	{
		first = 1;
		i = -1;
		while (++i < anthill->ant_len)
			if (((anthill->ant)[i])->next_p
			&& (anthill->ant)[i] != anthill->start)
			{
				(anthill->ant)[i] = ((anthill->ant)[i])->next_p;
				ft_printf("%s%d-%s"
				, (!first) ? " L" : "L", i + 1, ((anthill->ant)[i])->name);
				first = 0;
			}
		ft_push_ant(anthill, end_prev, len, first);
		ft_printf("\n");
	}
	free(len);
	return (1);
}

void	ft_print_map(t_anthill *anthill, t_map *tmp)
{
	char nb_ant_pr;

	nb_ant_pr = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->line, "##start") && ft_strcmp(tmp->line, "##end"))
		{
			if (tmp->next && !ft_strchr(tmp->line, '-'))
			{
				if (!ft_memcmp(tmp->line, anthill->start->name
				, ft_strlen(anthill->start->name)))
					ft_putstr("##start\n");
				else if (!ft_memcmp(tmp->line, anthill->end->name
				, ft_strlen(anthill->end->name)))
					ft_putstr("##end\n");
			}
			ft_printf("%s\n", tmp->line);
		}
		else if (tmp->line[0] != '#' && !nb_ant_pr)
		{
			nb_ant_pr = 1;
			ft_printf("%d\n", anthill->ant_len);
		}
		tmp = tmp->next;
	}
}

char	ft_print_res(t_anthill *anthill, t_room **end_prev)
{
	t_map	*tmp;

	tmp = anthill->map;
	if (!anthill->nbsteps)
	{
		ft_print_map(anthill, tmp);
		ft_printf("\n");
		if (!ft_print_move(anthill, end_prev))
			return (0);
	}
	else if (!ft_print_nbsteps(anthill, end_prev))
		return (0);
	return (1);
}
