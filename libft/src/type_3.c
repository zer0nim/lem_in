/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:14:17 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 11:52:33 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_p_x(t_p p, va_list list, int *n, char *res)
{
	char						*ret;
	unsigned	long	long	d;
	int							w[2];

	d = get_nb_u_casted(p, list);
	ft_get_width_ux(d, p, w, 16);
	if (d != 0 && (p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0x", n, -1))))
		return (NULL);
	if ((p.is_wdh && !p.min)
	&& !(res = put_width(w[1], res, ((p.is_pre) ? 0 : p.zer), n)))
		return (NULL);
	if (d != 0 && !(p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0x", n, -1))))
		return (NULL);
	if ((p.is_pre) && !(res = put_width(w[0], res, 1, n)))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0) && (!(ret = ft_itoa_bas_s(d, 16, 0))
	|| !(res = ft_realcat_z(res, ret, n, -1))))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0))
		free(ret);
	if ((p.is_wdh && p.min) && !(res = put_width(w[1], res, 0, n)))
		return (NULL);
	return (res);
}

char	*ft_p_x_b(t_p p, va_list list, int *n, char *res)
{
	char						*ret;
	unsigned	long	long	d;
	int							w[2];

	d = get_nb_u_casted(p, list);
	ft_get_width_ux(d, p, w, 16);
	if (d != 0 && (p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0X", n, -1))))
		return (NULL);
	if ((p.is_wdh && !p.min)
	&& !(res = put_width(w[1], res, ((p.is_pre) ? 0 : p.zer), n)))
		return (NULL);
	if (d != 0 && !(p.zer && !p.is_pre) && (p.hsh)
	&& (!(res = ft_realcat_z(res, "0X", n, -1))))
		return (NULL);
	if ((p.is_pre) && !(res = put_width(w[0], res, 1, n)))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0) && (!(ret = ft_itoa_bas_s(d, 16, 1))
	|| !(res = ft_realcat_z(res, ret, n, -1))))
		return (NULL);
	if (!(d == 0 && p.is_pre && p.pre == 0))
		free(ret);
	if ((p.is_wdh && p.min) && !(res = put_width(w[1], res, 0, n)))
		return (NULL);
	return (res);
}

char	*ft_p_c(t_p p, va_list list, int *n, char *res)
{
	long	c;

	c = (p.l) ? va_arg(list, unsigned int) : va_arg(list, int);
	if (c > 0xFFFF && MB_CUR_MAX == 4)
		p.wdh = ((((p.wdh) -= 3) > 0) ? p.wdh : 0);
	else if (c > 0x7FF && MB_CUR_MAX == 4)
		p.wdh = ((((p.wdh) -= 2) > 0) ? p.wdh : 0);
	else if (c > 0x7F && MB_CUR_MAX == 4)
		p.wdh = ((((p.wdh) -= 1) > 0) ? p.wdh : 0);
	if ((p.is_wdh && !p.min) && !(res = put_width(p.wdh, res, p.zer, n)))
		return (NULL);
	if (p.l)
	{
		if (ft_bad_uni(c))
		{
			free(res);
			return (NULL);
		}
		if (!(res = f_uni(res, n, c, &p)))
			return (NULL);
	}
	else if (!(res = ft_realcatc_z(res, c, n)))
		return (NULL);
	return (((p.is_wdh && p.min)
	&& !(res = put_width(p.wdh, res, p.zer, n))) ? (NULL) : (res));
}

char	*ft_p_c_b(t_p p, va_list list, int *n, char *res)
{
	long	c;

	c = va_arg(list, unsigned int);
	if (c > 0xFFFF && MB_CUR_MAX == 4)
		p.wdh = ((((p.wdh) -= 3) > 0) ? p.wdh : 0);
	else if (c > 0x7FF && MB_CUR_MAX == 4)
		p.wdh = ((((p.wdh) -= 2) > 0) ? p.wdh : 0);
	else if (c > 0x7F && MB_CUR_MAX == 4)
		p.wdh = ((((p.wdh) -= 1) > 0) ? p.wdh : 0);
	if (ft_bad_uni(c))
	{
		free(res);
		return (NULL);
	}
	if ((p.is_wdh && !p.min) && !(res = put_width(p.wdh, res, p.zer, n)))
		return (NULL);
	if (!(res = f_uni(res, n, c, &p)))
		return (NULL);
	if ((p.is_wdh && p.min) && !(res = put_width(p.wdh, res, p.zer, n)))
		return (NULL);
	return (res);
}

char	*ft_p_perc(t_p p, va_list list, int *n, char *res)
{
	while ((p.is_wdh && !p.min) && (p.wdh)-- > 1)
		if (!(res = ft_realcatc_z(res, (p.zer) ? '0' : ' ', n)))
			return (NULL);
	if (!(res = ft_realcatc_z(res, '%', n)))
		return (NULL);
	while ((p.is_wdh && p.min) && (p.wdh)-- > 1)
		if (!(res = ft_realcatc_z(res, ' ', n)))
			return (NULL);
	if (list)
		;
	return (res);
}
