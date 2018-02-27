/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:32:06 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 11:16:24 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*put_width(int len, char *res, char zer, int *n)
{
	while (len-- > 1)
		if (!(res = ft_realcatc_z(res, (zer) ? '0' : ' ', n)))
			return (NULL);
	return (res);
}

char	trn(char cond, char c_true, char c_false)
{
	return ((cond) ? c_true : c_false);
}

void	modif_p_for_p(t_p *p)
{
	p->hsh = 1;
	p->hh = 0;
	p->h = 0;
	p->ll = 1;
	p->l = 0;
	p->j = 0;
	p->z = 0;
}

size_t	ft_strlen_z(const char *s, int nbzer)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' || --nbzer > 0)
		i++;
	return (i);
}

char	*ft_strdup_z(const char *s1, int nbzer)
{
	char	*dest;
	int		i;

	if (NULL == (dest = (char *)malloc(sizeof(*s1) *
	(ft_strlen_z(((char*)s1), nbzer) + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0' || --nbzer > 0)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
