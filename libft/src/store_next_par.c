/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_next_par.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:19:40 by emarin            #+#    #+#             */
/*   Updated: 2018/01/04 20:01:04 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		store_pre(char **format, t_p *p)
{
	char	*nb;
	int		j;
	int		i;

	i = 0;
	if (!((*format)[1] && ft_isnb((*format)[1])))
	{
		p->is_pre = 1;
		p->pre = 0;
		return (1);
	}
	++(*format);
	j = 1;
	while ((*format)[j] && ft_isnb((*format)[j]))
		++j;
	if (!(nb = ft_strnew(j)))
		return (0);
	while (i < j)
		nb[i++] = *((*format)++);
	--(*format);
	nb[i] = '\0';
	p->is_pre = 1;
	p->pre = ft_atoi(nb);
	free(nb);
	return (1);
}

int		store_wdh(char **format, t_p *p)
{
	char	*nb;
	int		j;
	int		i;

	i = 0;
	j = 1;
	while ((*format)[j] && ft_isnb((*format)[j]))
		++j;
	if (!(nb = ft_strnew(j)))
		return (0);
	while (i < j)
	{
		nb[i] = *(*format);
		++(*format);
		++i;
	}
	--(*format);
	nb[i] = '\0';
	p->is_wdh = 1;
	p->wdh = ft_atoi(nb);
	free(nb);
	return (1);
}

void	store_l_h(char **format, t_p *p, int l)
{
	if (l)
	{
		if ((*format)[1] && (*format)[1] == 'l')
		{
			p->ll = 1;
			++(*format);
		}
		else
			p->l = 1;
	}
	else
	{
		if ((*format)[1] && (*format)[1] == 'h')
		{
			p->hh = 1;
			++(*format);
		}
		else
			p->h = 1;
	}
}

int		store_next_par2(char **format, t_p *p)
{
	if (*(*format) == 'h')
		store_l_h(format, p, 0);
	else if (*(*format) == 'l')
		store_l_h(format, p, 1);
	else if (*(*format) == 'j')
		p->j = 1;
	else if (*(*format) == 'z')
		p->z = 1;
	return (1);
}

int		store_next_par(char **format, t_p *p)
{
	if (*(*format) == '-')
		p->min = 1;
	else if (*(*format) == '+')
		p->add = 1;
	else if (*(*format) == ' ')
		p->spa = 1;
	else if (*(*format) == '#')
		p->hsh = 1;
	else if (*(*format) == '0')
		p->zer = 1;
	else if (ft_isnb(*(*format)))
	{
		if (!(store_wdh(format, p)))
			return (0);
	}
	else if (*(*format) == '.')
	{
		if (!(store_pre(format, p)))
			return (0);
	}
	else
		return (store_next_par2(format, p));
	return (1);
}
