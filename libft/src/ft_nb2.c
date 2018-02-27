/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:37:44 by emarin            #+#    #+#             */
/*   Updated: 2018/01/09 16:47:03 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char						*ft_itoa_u_long(unsigned long long value)
{
	unsigned	long	long	n;
	int							i;
	char						*ret;

	n = value;
	i = 1;
	while ((n /= 10) != 0)
		++i;
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[i] = '\0';
	n = value;
	while (n > 0 && --i >= 0)
	{
		ret[i] = (n % 10) + '0';
		n /= 10;
	}
	if (value == 0)
		ret[0] = '0';
	return (ret);
}

char						*ft_itoa_bas_s(unsigned long long value,
int base, char x)
{
	unsigned	long	long	n;
	int							i;
	char						*ret;
	char						eq_base[17];

	if (x)
		ft_strcpy(eq_base, "0123456789ABCDEF");
	else
		ft_strcpy(eq_base, "0123456789abcdef");
	n = value;
	i = 1;
	while ((n /= base) != 0)
		i++;
	if (!(ret = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[i] = '\0';
	n = value;
	while (n > 0 && --i >= 0)
	{
		ret[i] = eq_base[n % base];
		n /= base;
	}
	if (value == 0)
		ret[0] = '0';
	return (ret);
}

void						ft_get_width_ux(unsigned long long d, t_p p
, int w[2], int base)
{
	unsigned	long	long	n;
	int							i;

	w[0] = 0;
	w[1] = 0;
	n = d;
	i = 1;
	while ((n /= base) != 0)
		i++;
	if (d == 0 && p.is_pre && p.pre == 0)
		i = 0;
	if (p.is_pre)
	{
		while (i++ < p.pre)
			++(w[0]);
		i -= 1;
		++(w[0]);
	}
	if (p.hsh && d != 0)
		i += 2;
	if (p.is_wdh)
		while (i++ <= p.wdh)
			++(w[1]);
}

void						ft_get_width_p(unsigned long long d, t_p p
, int w[2], int base)
{
	unsigned	long	long	n;
	int							i;

	w[0] = 0;
	w[1] = 0;
	n = d;
	i = 1;
	while ((n /= base) != 0)
		i++;
	if (d == 0 && p.is_pre && p.pre == 0)
		i = 0;
	if (p.is_pre)
	{
		while (i++ < p.pre)
			++(w[0]);
		i -= 1;
		++(w[0]);
	}
	if (p.hsh)
		i += 2;
	if (p.is_wdh)
		while (i++ <= p.wdh)
			++(w[1]);
}

void						ft_get_width_uo(unsigned long long d, t_p p
, int w[2], int base)
{
	unsigned	long	long	n;
	int							i;

	w[0] = 0;
	w[1] = 0;
	n = d;
	i = 1;
	while ((n /= base) != 0)
		i++;
	if (d == 0 && p.is_pre && p.pre == 0)
		i = 0;
	if (p.is_pre)
	{
		while (i++ < p.pre)
			++(w[0]);
		i -= 1;
		++(w[0]);
	}
	if ((!p.is_pre || (p.is_pre && p.pre == 0)) && p.hsh
	&& (d != 0 || (p.is_pre && p.pre == 0)))
		i += 1;
	if (p.is_wdh)
		while (i++ <= p.wdh)
			++(w[1]);
}
