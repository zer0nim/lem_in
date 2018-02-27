/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:22:36 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:54:29 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		isfind;
	char	*lastfind;

	isfind = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			lastfind = &(((char*)s)[i]);
			isfind = 1;
		}
		i++;
	}
	if ((char)c == '\0')
		return (&(((char*)s)[i]));
	if (isfind)
		return (lastfind);
	return (NULL);
}
