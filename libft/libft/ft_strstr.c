/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:28:15 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:54:17 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int len;
	int lenneedle;

	len = ft_strlen((char *)haystack);
	lenneedle = ft_strlen((char *)needle);
	if (lenneedle <= 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && lenneedle <= (len - i))
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i] == needle[j])
		{
			j++;
			i++;
		}
		i = i - j;
		if (needle[j] == '\0')
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
