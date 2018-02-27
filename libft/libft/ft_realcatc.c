/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realcatc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:23:19 by emarin            #+#    #+#             */
/*   Updated: 2018/01/04 12:48:46 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realcatc(char *s1, char c)
{
	int		i;
	char	*str;

	if (!(str = ft_strnew(ft_strlen(s1) + 1)))
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		++i;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}
