/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:23:55 by emarin            #+#    #+#             */
/*   Updated: 2018/02/21 14:05:37 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	ft_change_start_end(char start_end, t_anthill *anthill, char **argv
, int i)
{
	t_room	*r;

	r = anthill->room;
	while (r && !is_equal(r->name, argv[i], '\n'))
		r = r->next;
	if (start_end && r != NULL)
		anthill->start = r;
	if (!start_end && r != NULL)
		anthill->end = r;
}

int		ft_bonus(t_anthill *anthill, int argc, char **argv)
{
	int i;

	i = 0;
	anthill->nbsteps = 0;
	while (++i < argc)
		if (!ft_memcmp(argv[i], "--nbstep", 8))
			anthill->nbsteps = 1;
		else if (!ft_memcmp(argv[i], "-nbant", 6))
		{
			if (++i < argc &&
			(ft_overflow(argv[i]) && ft_isnb(argv[i][0]) && argv[i][0] != '0'))
			{
				free(anthill->ant);
				if (!init_ant_len(anthill, argv[i]))
					return (0);
			}
		}
		else if (!ft_memcmp(argv[i], "-start", 6) && ++i < argc)
			ft_change_start_end(1, anthill, argv, i);
		else if (!ft_memcmp(argv[i], "-end", 4) && ++i < argc)
			ft_change_start_end(0, anthill, argv, i);
	if (anthill->start == anthill->end)
		return (0);
	return (1);
}

char	ft_lem_in(t_anthill *anthill)
{
	t_room	**end_prev;

	end_prev = NULL;
	ft_init_ant_pos(anthill);
	ft_dijkstra(anthill, 0);
	while ((anthill->end)->prev != NULL)
	{
		end_prev = ft_realcat_end_prev(end_prev, (anthill->end)->prev);
		ft_block_short(anthill);
		ft_dijkstra(anthill, 1);
		if ((anthill->end)->prev == anthill->start)
			(anthill->end)->prev = NULL;
	}
	if (!end_prev || !ft_print_res(anthill, end_prev))
		return (0);
	free(end_prev);
	ft_free_anthill(anthill);
	return (1);
}

int		main(int argc, char **argv)
{
	char		*line;
	char		state;
	t_anthill	anthill;

	state = 1;
	anthill.ant = NULL;
	anthill.room = NULL;
	anthill.start = NULL;
	anthill.end = NULL;
	line = NULL;
	while (ft_get_next_line(STDIN_FILENO, &line) > 0
	&& ft_parse_ant(&anthill, line, &state))
	{
		if (state == 4 && !anthill.start)
			anthill.start = anthill.room;
		else if (state == 5 && !anthill.end)
			anthill.end = anthill.room;
		state = (state == 4 || state == 5) ? 1 : state;
		ft_add_line(&anthill, line);
	}
	free(line);
	if (!ft_bonus(&anthill, argc, argv) || (!anthill.start || !anthill.end)
	|| !ft_lem_in(&anthill))
		return (ft_er(&anthill));
	return (0);
}
