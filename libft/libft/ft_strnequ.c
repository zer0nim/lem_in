/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:24:54 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:55:00 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& (unsigned char)s1[i] != '\0' && (unsigned char)s2[i] != '\0'
			&& i < n)
		i++;
	if (((unsigned char)s1[i] == '\0' && (unsigned char)s2[i] == '\0')
			|| (i >= n && (unsigned char)s1[i - 1] == (unsigned char)s2[i - 1])
				|| n <= 0)
		return (1);
	return (0);
}
