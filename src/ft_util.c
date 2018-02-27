/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:09:00 by emarin            #+#    #+#             */
/*   Updated: 2018/02/09 17:19:21 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		ft_nb_room(t_anthill *anthill)
{
	t_room	*tmp;
	int		len;

	len = 0;
	tmp = anthill->room;
	while (tmp)
	{
		++len;
		tmp = tmp->next;
	}
	return (len);
}

void	ft_init_ant_pos(t_anthill *anthill)
{
	int	i;

	i = 0;
	while (i < anthill->ant_len)
	{
		(anthill->ant)[i] = anthill->start;
		++i;
	}
}

int		ft_er(t_anthill *anthill)
{
	ft_free_anthill(anthill);
	ft_putstr_fd("ERROR\n", STDERR_FILENO);
	return (0);
}

void	ft_free_anthill(t_anthill *anthill)
{
	t_room	*tmp;

	ft_free_line(anthill);
	while (anthill->room)
	{
		tmp = (anthill->room);
		anthill->room = anthill->room->next;
		if (tmp->near)
		{
			free(tmp->near);
		}
		free(tmp->name);
		free(tmp);
	}
	free(anthill->ant);
}

char	ft_overflow(char *str)
{
	if (((long long)ft_atoi(str) != ft_atoi_l(str))
	|| ft_strlen(str) > 11)
		return (0);
	return (1);
}
