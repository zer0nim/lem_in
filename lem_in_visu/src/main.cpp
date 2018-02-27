/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:29:13 by emarin            #+#    #+#             */
/*   Updated: 2018/02/15 11:53:32 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_visu.h"

char	ft_lem_in_visu(t_anthill *anthill)
{
	ft_init_ant_pos(anthill);

	start_lem_in_visu(anthill);

	ft_free_anthill(anthill);
	return (1);
}

int		main(void)
{
	char		*line;
	char		state;
	t_anthill	anthill;

	state = 1;
	anthill.ant = NULL;
	anthill.room = NULL;
	anthill.start = NULL;
	anthill.end = NULL;
	while (ft_get_next_line(STDIN_FILENO, &line)
	&& ft_parse_ant(&anthill, line, &state))
	{
		if (state == 4 && !anthill.start)
			anthill.start = anthill.room;
		else if (state == 5 && !anthill.end)
			anthill.end = anthill.room;
		state = (state == 4 || state == 5) ? 1 : state;
		free(line);
	}
	free(line);
	if (!anthill.start || !anthill.end)
		return (ft_er(&anthill));
	if (!ft_lem_in_visu(&anthill))
		return (ft_er(&anthill));
	return (0);
}
