/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:21:13 by emarin            #+#    #+#             */
/*   Updated: 2018/02/21 14:13:26 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H

# include "libft/ft_printf.h"

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
	struct s_room	**near;
	int				dist;
	char			found;
	struct s_room	*prev;
	struct s_room	*next_p;
}					t_room;

typedef struct		s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct		s_anthill
{
	int				ant_len;
	t_room			**ant;
	t_room			*room;
	t_room			*start;
	t_room			*end;
	t_map			*map;
	char			nbsteps;
}					t_anthill;

int					ft_er(t_anthill *anthill);
char				ft_parse_ant(t_anthill *anthill, char *line, char *state);
char				init_ant_len(t_anthill *anthill, char *line);
void				add_room(t_anthill *anthill, t_room *room);
char				ft_set_near(t_room *a, t_room *b);
char				ft_overflow(char *str);
void				ft_free_anthill(t_anthill *anthill);
void				ft_dijkstra(t_anthill *anthill, char reinit);
t_room				**ft_realcat_end_prev(t_room **end_prev, t_room *new_prev);
void				ft_block_short(t_anthill *anthill);
void				ft_print_near(t_room *crnt, t_room **near, t_room *room
, int pos);
int					*ft_get_path_len(t_room **end_prev);
void				ft_add_next_path(t_anthill *anthill, t_room **end_prev);
char				ft_print_res(t_anthill *anthill, t_room **end_prev);
void				ft_init_ant_pos(t_anthill *anthill);
char				ft_check_alrdy_print(t_room *crnt, t_room *near
, t_room *room, int pos);
char				ft_add_line(t_anthill *anthill, char *line);
void				ft_free_line(t_anthill *anthill);
int					ft_nb_room(t_anthill *anthill);
void				ft_push_ant_nbsteps(t_anthill *anthill, t_room **end_prev
, int *len, char first);
char				ft_print_nbsteps(t_anthill *anthill, t_room **end_prev);
char				ft_is_empty(t_anthill *anthill, t_room *room);
char				is_equal(char *name, char *line, char separator);

#endif
