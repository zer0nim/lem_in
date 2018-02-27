/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:54:06 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:54:22 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		nextword(char *s, char c, int i)
{
	while (s[i] != '\0' && s[i] == c)
		i++;
	return (i);
}

static	int		nbword(char *s, char c)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = nextword(s, c, 0);
	while (s[i] != '\0')
	{
		cnt++;
		while (s[i] != '\0' && s[i] != c)
			i++;
		i = nextword(s, c, i);
	}
	return (cnt);
}

static	char	**allocarray(char *s, char c)
{
	int		j;
	int		i;
	int		len;
	char	**res;

	if (NULL == (res = (char **)malloc(sizeof(char*) * (nbword(s, c) + 1))))
		return (NULL);
	j = 0;
	i = nextword(s, c, 0);
	while (s[i] != '\0')
	{
		len = 0;
		while (s[i] != '\0' && s[i] != c)
		{
			len++;
			i++;
		}
		if (NULL == (res[j] = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		i = nextword(s, c, i);
		j++;
	}
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		its;
	char	**res;

	res = allocarray((char*)s, c);
	if (NULL == res)
		return (NULL);
	j = 0;
	its = nextword((char*)s, c, 0);
	while (s[its] != '\0')
	{
		i = 0;
		while (s[its] != '\0' && s[its] != c)
		{
			res[j][i] = s[its];
			i++;
			its++;
		}
		res[j][i] = '\0';
		its = nextword((char*)s, c, its);
		j++;
	}
	res[j] = NULL;
	return (res);
}
