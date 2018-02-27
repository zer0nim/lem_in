/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:14:27 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 12:13:51 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_p_other(t_p p, int *n, char *res, unsigned int c)
{
	if ((p.is_wdh && !p.min) && !(res = put_width(p.wdh, res, p.zer, n)))
		return (NULL);
	if (c && (!(res = ft_realcatc_z(res, c, n))))
		return (NULL);
	if ((p.is_wdh && p.min) && !(res = put_width(p.wdh, res, p.zer, n)))
		return (NULL);
	return (res);
}

char	*ft_p_b(t_p p, va_list list, int *n, char *res)
{
	char						*ret;
	unsigned	long	long	d;
	int							w[2];

	d = get_nb_u_casted(p, list);
	ft_get_width_ux(d, p, w, 2);
	if (d != 0 && (p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0b", n, -1))))
		return (NULL);
	if ((p.is_wdh && !p.min)
	&& !(res = put_width(w[1], res, ((p.is_pre) ? 0 : p.zer), n)))
		return (NULL);
	if (d != 0 && !(p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0b", n, -1))))
		return (NULL);
	if ((p.is_pre) && !(res = put_width(w[0], res, 1, n)))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0) && (!(ret = ft_itoa_bas_s(d, 2, 0))
	|| !(res = ft_realcat_z(res, ret, n, -1))))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0))
		free(ret);
	if ((p.is_wdh && p.min) && !(res = put_width(w[1], res, 0, n)))
		return (NULL);
	return (res);
}
