/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:57:38 by emarin            #+#    #+#             */
/*   Updated: 2018/02/09 15:39:14 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char	ft_add_line(t_anthill *anthill, char *line)
{
	t_map	*map;
	t_map	*tmp;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (0);
	map->line = line;
	map->next = NULL;
	if (!anthill->map)
		anthill->map = map;
	else
	{
		tmp = anthill->map;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = map;
	}
	return (1);
}

void	ft_free_line(t_anthill *anthill)
{
	t_map	*tmp;

	if (anthill->map)
	{
		tmp = anthill->map;
		while (anthill->map)
		{
			tmp = anthill->map;
			anthill->map = (anthill->map)->next;
			free(tmp->line);
			free(tmp);
		}
	}
}
