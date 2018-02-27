/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 15:36:25 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 11:48:38 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static	char	*f_er_uni(char *res, t_p *p)
{
	p->pre = 0;
	return (res);
}

char			*f_uni(char *res, int *n, long c, t_p *p)
{
	unsigned int u;

	if (MB_CUR_MAX == 1)
		return ((!(res = ft_realcatc_z(res, c, n))) ? NULL : res);
	u = uni(c);
	if (c > 0xFFFF && c <= 0x1FFFFF && ((--(p->pre)) < 0 || p->pre >= 0))
		if (p->is_pre && ((p->pre) + 1 < 3))
			return (f_er_uni(res, p));
	if (c > 0xFFFF && c <= 0x1FFFFF && (p->pre < 0 || p->pre >= 0))
		if (!(res = ft_realcatc_z(res, (u & 0xFF000000) >> 24, n)))
			return (NULL);
	if (c > 0x7FF && c <= 0x1FFFFF && ((--(p->pre)) < 0 || p->pre >= 0))
		if (p->is_pre && ((p->pre) + 1 < 2))
			return (f_er_uni(res, p));
	if (c > 0x7FF && c <= 0x1FFFFF && (p->pre < 0 || p->pre >= 0))
		if (!(res = ft_realcatc_z(res, (u & 0x00FF0000) >> 16, n)))
			return (NULL);
	if (c > 0x7F && c <= 0x1FFFFF && ((--(p->pre)) < 0 || p->pre >= 0))
		if (p->is_pre && ((p->pre) + 1 < 1))
			return (f_er_uni(res, p));
	if (c > 0x7F && c <= 0x1FFFFF && (p->pre < 0 || p->pre >= 0))
		if (!(res = ft_realcatc_z(res, (u & 0x0000FF00) >> 8, n)))
			return (NULL);
	return ((c <= 0x1FFFFF
		&& !(res = ft_realcatc_z(res, u & 0x000000FF, n))) ? NULL : res);
}

unsigned	int	uni(unsigned int c)
{
	unsigned int r;

	r = 0;
	if (c <= 0b01111111)
		return (c);
	else if (c <= 0b11111111111)
	{
		r = 0b1100000010000000 | (c & 0b111111) | ((c & 0b11111000000) << 2);
		if (MB_CUR_MAX == 1 && c <= 255)
			return (c);
	}
	else if (c <= 0b1111111111111111)
	{
		r = (0b111000001000000010000000) | (c & 0b111111)
			| ((c & 0b111111000000) << 2)
			| ((c & 0b1111000000000000) << 4);
	}
	else if (c <= 0b111111111111111111111)
	{
		r = (0 | 0b11110000100000001000000010000000) | (c & 0b111111)
			| ((c & 0b111111000000) << 2)
			| ((c & 0b111111000000000000) << 4)
			| ((c & 0b111000000000000000000) << 6);
	}
	return (r);
}

char			ft_bad_uni(unsigned	int c)
{
	return ((MB_CUR_MAX == 1 && c > 255) || c > 0xE01EF
	|| (c >= 0xD800 && c <= 0xDB7F) || (c >= 0xDC00 && c <= 0xDFFF));
}
