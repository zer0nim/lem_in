/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:53:14 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:53:57 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*res;
	int		i;
	int		st;
	int		j;

	st = 0;
	while (s[st] != '\0' && (s[st] == ' ' || s[st] == '\n' || s[st] == '\t'))
		st++;
	if (s[st] == '\0')
	{
		if (NULL == (res = (char *)malloc(sizeof(char))))
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	i = ft_strlen((char *)s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	if (NULL == (res = (char *)malloc(sizeof(char) * ((i - st) + 2))))
		return (NULL);
	j = 0;
	while (st <= i)
		res[j++] = s[st++];
	res[j] = '\0';
	return (res);
}
