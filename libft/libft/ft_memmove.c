/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:55:23 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:56:35 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = ((char*)dst);
	s = ((char*)src);
	if (len <= 0)
		return (dst);
	if (((char*)src) >= ((char*)dst))
		ft_memcpy(((char*)dst), ((char*)src), len);
	else
	{
		d = d + len - 1;
		s = s + len - 1;
		while (len > 0)
		{
			*d-- = *s--;
			len--;
		}
		((char*)dst)[len] = ((char*)src)[len];
	}
	return (dst);
}
