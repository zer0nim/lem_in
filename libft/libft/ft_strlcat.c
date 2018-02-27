/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:49:25 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:55:33 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	int		n;
	size_t	j;
	int		d_sz;

	i = 0;
	j = 0;
	d_sz = ft_strlen(dst);
	n = size - d_sz - 1;
	if (n > 0)
	{
		while (dst[i] != '\0')
			i++;
		while (src[j] != '\0' && (int)j < n)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (((d_sz > (int)size) ? size : d_sz) + ft_strlen((char*)src));
	}
	return (((d_sz > (int)size) ? size : d_sz) + ft_strlen((char*)src));
}
