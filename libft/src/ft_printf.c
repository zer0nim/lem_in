/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:52:51 by emarin            #+#    #+#             */
/*   Updated: 2018/01/10 19:07:14 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	init_p(t_p *p)
{
	p->min = 0;
	p->add = 0;
	p->zer = 0;
	p->spa = 0;
	p->hsh = 0;
	p->is_wdh = 0;
	p->is_pre = 0;
	p->hh = 0;
	p->h = 0;
	p->l = 0;
	p->ll = 0;
	p->j = 0;
	p->z = 0;
}

char	*do_arg(char **fm, va_list list, int *n, char *res)
{
	int		j;
	t_p		p;

	init_p(&p);
	j = 0;
	while (*(++(*fm)) && ft_strchr(" #-+hljz.0123456789", *(*fm))
		&& !ft_strchr("sSpdDioOuUxXcC%", *(*fm)))
	{
		if (!(store_next_par(fm, &p)))
			return (NULL);
	}
	while (g_typ[j].key != '>' && g_typ[j].key != *(*fm))
		++j;
	if (g_typ[j].key == '>')
	{
		if (!*(*fm))
		{
			--(*fm);
			return (ft_p_other(p, n, res, 0));
		}
		return (ft_p_other(p, n, res, *(*fm)));
	}
	return (g_typ[j].f(p, list, n, res));
}

int		ft_printf(const char *format, ...)
{
	char	*cop_f;
	char	*res;
	char	*tmp;
	va_list	list;
	int		n;

	tmp = NULL;
	cop_f = (char *)format - 1;
	if (!(res = ft_strnew(0)))
		return (-1);
	va_start(((n = 1) ? list : list), format);
	while (*(++cop_f))
		if (*cop_f == '%')
		{
			if (!(res = do_arg(&(cop_f), list, &n, res)))
				return (ft_putstr_z(tmp, n, 1));
			free((tmp) ? tmp : NULL);
			if (!(tmp = ft_strdup_z(res, n)))
				return (-1);
		}
		else if (!(res = ft_realcatc_z(res, *cop_f, &n)))
			return (-1);
	va_end(list);
	free(tmp);
	return (ft_putstr_z(res, n, 0));
}
