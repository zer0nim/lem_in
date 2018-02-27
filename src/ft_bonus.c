/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:26:58 by emarin            #+#    #+#             */
/*   Updated: 2018/02/21 14:04:31 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	ft_push_ant_nbsteps(t_anthill *anthill, t_room **end_prev, int *len
, char first)
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
				first = 0;
			}
		}
		++i;
	}
}

char	ft_print_nbsteps(t_anthill *anthill, t_room **end_prev)
{
	int		*len;
	int		i;
	char	first;
	int		nbsteps;

	nbsteps = 0;
	if (!(len = ft_get_path_len(end_prev)))
		return (0);
	ft_add_next_path(anthill, end_prev);
	while ((anthill->ant)[anthill->ant_len - 1] != anthill->end && ++nbsteps)
	{
		first = 1;
		i = -1;
		while (++i < anthill->ant_len)
			if (((anthill->ant)[i])->next_p
			&& (anthill->ant)[i] != anthill->start)
			{
				(anthill->ant)[i] = ((anthill->ant)[i])->next_p;
				first = 0;
			}
		ft_push_ant_nbsteps(anthill, end_prev, len, first);
	}
	ft_printf("%d\n", nbsteps);
	free(len);
	return (1);
}
