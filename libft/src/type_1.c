/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:13:58 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 11:45:40 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_p_s(t_p p, va_list list, int *n, char *res)
{
	unsigned	int	*s;
	int				iw[2];

	s = va_arg(list, unsigned int *);
	iw[1] = ft_get_width(s, p, p.l, 0);
	if (((p.is_wdh && !p.min) && !(res = put_width(iw[1], res, p.zer, n)))
	|| (!s && !(p.is_pre && p.pre == 0)
	&& (!(res = ft_realcat_z(res, "(null)", n, ((p.is_pre) ? p.pre : -1))))))
		return (NULL);
	else if ((iw[0] = -1) == -1 && s)
	{
		while (((!p.l && ((char *)s)[++(iw[0])]) || (p.l && s[++(iw[0])]))
		&& (!p.is_pre || (p.is_pre && p.pre-- > 0)))
			if (!p.l && !(res = ft_realcatc_z(res, ((char *)s)[(iw[0])], n)))
				return (NULL);
			else if (p.l && ft_bad_uni(s[iw[0]]))
			{
				free(res);
				return (NULL);
			}
			else if (p.l && !(res = f_uni(res, n, s[(iw[0])], &p)))
				return (NULL);
	}
	return (((p.is_wdh && p.min)
	&& !(res = put_width(iw[1], res, 0, n))) ? (NULL) : res);
}

char	*ft_p_s_b(t_p p, va_list list, int *n, char *res)
{
	unsigned	int	*s;
	int				iw[2];

	s = va_arg(list, unsigned int *);
	iw[1] = ft_get_width(s, p, 1, 0);
	if (((p.is_wdh && !p.min) && !(res = put_width(iw[1], res, p.zer, n)))
	|| (!s && !(p.is_pre && p.pre == 0)
	&& (!(res = ft_realcat_z(res, "(null)", n, ((p.is_pre) ? p.pre : -1))))))
		return (NULL);
	else if ((iw[0] = -1) == -1 && s)
	{
		while (s[++(iw[0])] && (!p.is_pre || (p.is_pre && p.pre-- > 0)))
		{
			if (ft_bad_uni(s[iw[0]]))
			{
				free(res);
				return (NULL);
			}
			else if (!(res = f_uni(res, n, s[iw[0]], &p)))
				return (NULL);
		}
	}
	if ((p.is_wdh && p.min) && !(res = put_width(iw[1], res, 0, n)))
		return (NULL);
	return (res);
}

char	*ft_p_p(t_p p, va_list list, int *n, char *res)
{
	char						*ret;
	unsigned	long	long	d;
	int							w[2];

	modif_p_for_p(&p);
	d = get_nb_u_casted(p, list);
	ft_get_width_p(d, p, w, 16);
	if ((p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0x", n, -1))))
		return (NULL);
	if ((p.is_wdh && !p.min)
	&& !(res = put_width(w[1], res, ((p.is_pre) ? 0 : p.zer), n)))
		return (NULL);
	if (!(p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0x", n, -1))))
		return (NULL);
	if ((p.is_pre) && !(res = put_width(w[0], res, 1, n)))
		return (NULL);
	if (!(p.is_pre && p.pre == 0) && (!(ret = ft_itoa_bas_s(d, 16, 0))
	|| !(res = ft_realcat_z(res, ret, n, -1))))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0))
		free(ret);
	return (((p.is_wdh && p.min)
	&& !(res = put_width(w[1], res, 0, n))) ? (NULL) : (res));
}

char	*ft_p_d(t_p p, va_list list, int *n, char *res)
{
	char			*ret;
	long	long	d;
	int				w[2];

	d = get_nb_casted(p, list);
	ft_get_width_d(d, p, w);
	if ((p.zer && !p.is_pre) && (p.spa || p.add || d < 0)
	&& (!(res = ft_realcatc_z(res, ((d < 0) ? '-' : trn(p.add, '+', ' ')), n))))
		return (NULL);
	if ((p.is_wdh && !p.min)
	&& !(res = put_width(w[1], res, ((p.is_pre) ? 0 : p.zer), n)))
		return (NULL);
	if (!(p.zer && !p.is_pre) && (p.spa || p.add || d < 0)
	&& (!(res = ft_realcatc_z(res, ((d < 0) ? '-' : trn(p.add, '+', ' ')), n))))
		return (NULL);
	if ((p.is_pre) && !(res = put_width(w[0], res, 1, n)))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0) && (!(ret = ft_itoa_long(d))
	|| !(res = ft_realcat_z(res, ret, n, -1))))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0))
		free(ret);
	if ((p.is_wdh && p.min) && !(res = put_width(w[1], res, 0, n)))
		return (NULL);
	return (res);
}

char	*ft_p_d_b(t_p p, va_list list, int *n, char *res)
{
	p.hh = 0;
	p.h = 0;
	p.ll = 1;
	p.l = 0;
	p.j = 0;
	p.z = 0;
	return (ft_p_d(p, list, n, res));
}
