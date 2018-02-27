/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:45:52 by emarin            #+#    #+#             */
/*   Updated: 2018/01/06 18:23:48 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_putnb(char *res, int n)
{
	int		i;
	char	c[2];

	c[1] = '\0';
	i = 0;
	if (n == -2147483648)
	{
		ft_strcat(res, "-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_strcat(res, "-");
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnb(res, n / 10);
		ft_putnb(res, n % 10);
	}
	else
	{
		c[0] = n + '0';
		ft_strcat(res, c);
	}
}

char			*ft_itoa(int n)
{
	int		n_cop;
	int		s;
	char	*r;

	if (n != -2147483648)
	{
		s = (n <= 0) ? 2 : 1;
		n_cop = (n < 0) ? -n : n;
		while (n_cop > 0)
		{
			n_cop = n_cop / 10;
			++s;
		}
		if (NULL == (r = (char *)malloc(sizeof(char) * s)))
			return (NULL);
	}
	else
	{
		if (NULL == (r = (char *)malloc(sizeof(char) * 12)))
			return (NULL);
	}
	r[0] = '\0';
	ft_putnb(r, n);
	return (r);
}
