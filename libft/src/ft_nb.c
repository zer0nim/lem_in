/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 18:25:16 by emarin            #+#    #+#             */
/*   Updated: 2018/01/08 16:49:17 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void						ft_get_width_d(long long d, t_p p, int w[2])
{
	unsigned	long	long	n;
	int							i;

	w[0] = 0;
	w[1] = 0;
	n = (d < 0) ? (unsigned long long)-d : (unsigned long long)d;
	i = 1;
	while ((n /= 10) != 0)
		++i;
	if (d == 0 && p.is_pre && p.pre == 0)
		i = 0;
	if (p.is_pre)
	{
		while (i++ < p.pre)
			++(w[0]);
		i -= 1;
		++(w[0]);
	}
	if (p.spa || p.add || d < 0)
		++i;
	if (p.is_wdh)
		while (i++ <= p.wdh)
			++(w[1]);
}

void						ft_get_width_ud(unsigned long long d, t_p p
, int w[2])
{
	unsigned	long	long	n;
	int							i;

	w[0] = 0;
	w[1] = 0;
	n = d;
	i = 1;
	while ((n /= 10) != 0)
		++i;
	if (d == 0 && p.is_pre && p.pre == 0)
		i = 0;
	if (p.is_pre)
	{
		while (i++ < p.pre)
			++(w[0]);
		i -= 1;
		++(w[0]);
	}
	if (p.is_wdh)
		while (i++ <= p.wdh)
			++(w[1]);
}

long	long				get_nb_casted(t_p p, va_list list)
{
	if (p.j)
		return (va_arg(list, intmax_t));
	if (p.z)
		return (va_arg(list, size_t));
	if (p.ll)
		return (va_arg(list, long long));
	if (p.l)
		return (va_arg(list, long));
	if (p.h)
		return ((short)va_arg(list, int));
	if (p.hh)
		return ((char)va_arg(list, int));
	return (va_arg(list, int));
}

unsigned	long	long	get_nb_u_casted(t_p p, va_list list)
{
	if (p.j)
		return (va_arg(list, uintmax_t));
	if (p.z)
		return (va_arg(list, size_t));
	if (p.ll)
		return (va_arg(list, unsigned long long));
	if (p.l)
		return (va_arg(list, unsigned long));
	if (p.h)
		return ((unsigned short)va_arg(list, unsigned int));
	if (p.hh)
		return ((unsigned char)va_arg(list, unsigned int));
	return (va_arg(list, unsigned int));
}

char						*ft_itoa_long(long long value)
{
	unsigned	long	long	n;
	int							i;
	char						*ret;

	n = (value < 0) ? (unsigned long long)-value : (unsigned long long)value;
	i = 1;
	while ((n /= 10) != 0)
		++i;
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[0] = '-';
	ret[i] = '\0';
	n = (value < 0) ? (unsigned long long)-value : (unsigned long long)value;
	while (n > 0 && --i >= 0)
	{
		ret[i] = (n % 10) + '0';
		n /= 10;
	}
	if (value == 0)
		ret[0] = '0';
	return (ret);
}
