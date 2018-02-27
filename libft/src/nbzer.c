/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbzer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:48:36 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 11:29:16 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char			*ft_realcat_z(char *s1, const char *s2, int *nbzer, int pr)
{
	int		i;
	size_t	j;
	char	*str;
	int		cop_nbzer;

	cop_nbzer = (*nbzer);
	if (!(str = ft_strnew(ft_strlen_z(s1, *nbzer) + ft_strlen(s2)
	- ((pr != -1 && pr < 6) ? 6 - pr : 0))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0' || --cop_nbzer > 0)
	{
		str[i] = s1[i];
		++i;
	}
	while (s2[j] != '\0' && (pr == -1 || pr-- > 0))
	{
		str[i] = s2[j];
		++i;
		++j;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char			*ft_realcatc_z(char *s1, char c, int *nbzer)
{
	int		i;
	char	*str;
	int		cop_nbzer;

	cop_nbzer = (*nbzer);
	if (!(str = ft_strnew(ft_strlen_z(s1, *nbzer) + 1)))
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i] != '\0' || --cop_nbzer > 0)
	{
		str[i] = s1[i];
		++i;
	}
	str[i] = c;
	str[i + 1] = '\0';
	if (c == 0)
		++(*nbzer);
	free(s1);
	return (str);
}

int				ft_putstr_z(char *s, int nbzer, char er)
{
	int	len;

	if (!s)
		return (-1);
	len = 0;
	while (s[len] || --nbzer > 0)
		len++;
	write(1, s, len);
	free(s);
	if (er)
		return (-1);
	return (len);
}

static	char	check_p(t_p p, int n)
{
	return (!p.is_pre || (p.is_pre && n < p.pre));
}

int				ft_get_width(unsigned int *s, t_p p, char l, int n)
{
	char	ch;
	int		i;

	i = -1;
	while (!(ch = 0) && s && ((((char *)s)[++i] && !l) || (l && s[i]))
	&& check_p(p, n))
		if ((MB_CUR_MAX == 4 && s[i] > 0xFFFF && s[i] <= 0x1FFFFF
		&& (n += 4) > 0 && ((p.pre -= 4) < 0 || p.pre >= 0))
		&& ((ch = 1) && p.is_pre && (p.pre + 1 < 3) && (n -= 4) >= 0
		&& !(p.pre = 0)))
			break ;
		else if ((ch == 0 && MB_CUR_MAX == 4 && s[i] > 0x7FF && s[i] <= 0x1FFFFF
		&& (n += 3) > 0 && ((p.pre -= 3) < 0 || p.pre >= 0))
		&& ((ch = 1) && p.is_pre && ((p.pre) + 1 < 2) && (n -= 3) >= 0
			&& !(p.pre = 0)))
			break ;
		else if ((ch == 0 && MB_CUR_MAX == 4 && s[i] > 0x7F && s[i] <= 0x1FFFFF
		&& (n += 2) > 0 && ((p.pre -= 2) < 0 || p.pre >= 0))
		&& ((ch = 1) && p.is_pre && ((p.pre) + 1 < 1) && (n -= 2) >= 0
			&& !(p.pre = 0)))
			break ;
		else if (ch == 0)
			++n;
	return ((!s && !(p.is_pre && p.pre == 0)) ? (p.wdh - 6 + 1
	+ trn((p.is_pre && p.pre < 6), 6 - p.pre, 0)) : (p.wdh - n + 1));
}
