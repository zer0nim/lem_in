/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:00:52 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 14:19:19 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_list	*ft_freelst(int fd, t_list *lstfd)
{
	t_list	*last;
	t_list	*top;

	top = lstfd;
	last = lstfd;
	while (lstfd->next != NULL && ((t_line*)(lstfd->content))->fd != fd)
	{
		last = lstfd;
		lstfd = lstfd->next;
	}
	free(((t_line*)(lstfd->content))->buff);
	free((t_line*)(lstfd->content));
	if (top != lstfd)
		last->next = lstfd->next;
	else
		top = lstfd->next;
	free(lstfd);
	return (top);
}

static	int		ft_read(int fd, t_list **lstfd, int first, int *aswrite)
{
	int		nb;
	char	*buff;

	if (first)
	{
		if (!(((t_line*)((*lstfd)->content))->buff =
			(char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		{
			*lstfd = ft_freelst(fd, *lstfd);
			return (-1);
		}
	}
	buff = ((t_line*)((*lstfd)->content))->buff;
	if ((nb = read(fd, buff, BUFF_SIZE)) == -1)
	{
		*lstfd = ft_freelst(fd, *lstfd);
		return (-1);
	}
	buff[nb] = '\0';
	*aswrite = (nb == 0) ? 0 : *aswrite;
	return (nb);
}

static	int		ft_pushbuff(char **l, int first, t_list *lstfd)
{
	int		i;
	char	*buff;
	char	*realc;

	buff = ((t_line*)(lstfd->content))->buff;
	i = ((t_line*)(lstfd->content))->i;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!first)
	{
		if (!(realc = (char *)malloc(sizeof(char) * (ft_strlen(*l) + i + 2))))
			return (-1);
		ft_strcpy(realc, *l);
		free((*l));
		*l = realc;
	}
	else if (!(*l = (char *)malloc(sizeof(char) * (i + 1)))
		|| ((*l)[0] = '\0'))
		return (-1);
	*l = ft_strncat(*l, buff + ((t_line*)(lstfd->content))->i,
		(i - ((t_line*)(lstfd->content))->i));
	if (buff[i])
		return (!(!(((t_line*)(lstfd->content))->i = i + 1)));
	((t_line*)(lstfd->content))->i = 0;
	return (0);
}

static	int		ft_loop(t_list **lstfd, const int fd, char **line, int nbwr[3])
{
	int		rval;
	t_list	*res;
	int		useless;

	res = *lstfd;
	while (res->next != NULL && ((t_line*)(res->content))->fd != fd)
		res = res->next;
	if ((rval = ft_pushbuff(line, 1, res)) != 0)
		return (rval);
	while (nbwr[0] > 0)
	{
		if ((nbwr[0] = ft_read(fd, &res, 0, &useless)) == -1)
			return (-1);
		if ((rval = ft_pushbuff(line, 0, res)) != 0)
			return (rval);
	}
	*lstfd = ft_freelst(fd, *lstfd);
	return (nbwr[1]);
}

int				ft_get_next_line(const int fd, char **line)
{
	static	t_list	*l;
	t_list			*res;
	t_line			elem;
	int				nbwr[3];

	if ((nbwr[1] = 1) && (fd < 0 || line == NULL || BUFF_SIZE < 0))
		return (-1);
	elem.fd = fd;
	elem.i = 0;
	if ((nbwr[2] = (l == NULL) ? 1 : 2) && l == NULL)
		l = ft_lstnew(&elem, sizeof(t_line));
	else
	{
		res = l;
		while (res->next != NULL && ((t_line*)(res->content))->fd != fd)
			res = res->next;
		if (((nbwr[0] = ft_strlen(((t_line*)(res->content))->buff)) >= 0)
			&& (nbwr[2] = (!(((t_line*)(res->content))->fd == fd)) ? 1 : 2)
			&& !(((t_line*)(res->content))->fd == fd))
			ft_lstadd(&l, ft_lstnew(&elem, sizeof(t_line)));
		else if (((t_line*)(res->content))->i == nbwr[0])
			nbwr[1] = 0;
	}
	return (((nbwr[2] == 1 && ((nbwr[0] = ft_read(fd, &l, 1, nbwr + 1)) == -1))
		? -1 : ft_loop(&l, fd, line, nbwr)));
}
