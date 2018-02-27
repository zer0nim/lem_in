/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:14:07 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 11:32:33 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_p_o(t_p p, va_list list, int *n, char *res)
{
	char						*ret;
	unsigned	long	long	d;
	int							w[2];

	d = get_nb_u_casted(p, list);
	ft_get_width_uo(d, p, w, 8);
	if ((p.zer && !p.is_pre && p.hsh && (d != 0
	|| (p.is_pre && p.pre == 0)))
	&& (!(res = ft_realcatc_z(res, '0', n))))
		return (NULL);
	if ((p.is_wdh && !p.min)
	&& !(res = put_width(w[1], res, ((p.is_pre) ? 0 : p.zer), n)))
		return (NULL);
	if ((((!p.zer && !p.is_pre) || (p.is_pre && p.pre == 0)) && p.hsh && (d != 0
	|| (p.is_pre && p.pre == 0)))
	&& (!(res = ft_realcatc_z(res, '0', n))))
		return (NULL);
	if (((p.is_pre) && !(res = put_width(w[0], res, 1, n)))
	|| (!(p.is_pre && p.pre == 0 && d == 0) && (!(ret = ft_itoa_bas_s(d, 8, 0))
	|| !(res = ft_realcat_z(res, ret, n, -1)))))
		return (NULL);
	if (!(p.is_pre && p.pre == 0))
		free(ret);
	return (((p.is_wdh && p.min)
	&& !(res = put_width(w[1], res, 0, n))) ? (NULL) : (res));
}

char	*ft_p_o_b(t_p p, va_list list, int *n, char *res)
{
	p.hh = 0;
	p.h = 0;
	p.ll = 0;
	p.l = 1;
	p.j = 0;
	p.z = 0;
	return (ft_p_o(p, list, n, res));
}

char	*ft_p_u(t_p p, va_list list, int *n, char *res)
{
	char						*ret;
	unsigned	long	long	d;
	int							w[2];

	d = get_nb_u_casted(p, list);
	ft_get_width_ud(d, p, w);
	if ((p.is_wdh && !p.min)
	&& !(res = put_width(w[1], res, ((p.is_pre) ? 0 : p.zer), n)))
		return (NULL);
	if ((p.is_pre) && !(res = put_width(w[0], res, 1, n)))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0) && (!(ret = ft_itoa_u_long(d))
	|| !(res = ft_realcat_z(res, ret, n, -1))))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0))
		free(ret);
	if ((p.is_wdh && p.min) && !(res = put_width(w[1], res, 0, n)))
		return (NULL);
	return (res);
}

char	*ft_p_u_b(t_p p, va_list list, int *n, char *res)
{
	p.hh = 0;
	p.h = 0;
	p.ll = 1;
	p.l = 0;
	p.j = 0;
	p.z = 0;
	return (ft_p_u(p, list, n, res));
}
