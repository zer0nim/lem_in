/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:29:27 by emarin            #+#    #+#             */
/*   Updated: 2018/01/11 14:06:45 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <locale.h>

typedef struct				s_p
{
	char		min;
	char		add;
	char		zer;
	char		spa;
	char		hsh;

	char		is_wdh;
	long long	wdh;

	char		is_pre;
	long long	pre;

	char		hh;
	char		h;
	char		l;
	char		ll;
	char		j;
	char		z;
}							t_p;

int							ft_printf(const char *format, ...);
int							store_next_par(char **format, t_p *p);
unsigned	int				uni(unsigned int c);
char						*f_uni(char *res, int *n, long c, t_p *p);
char						*ft_realcatc_z(char *s1, char c, int *nbzer);
char						*ft_realcat_z(char *s1, const char *s2, int *nbzer
, int pr);
int							ft_putstr_z(char *s, int nbzer, char er);
int							ft_get_width(unsigned int *s, t_p p, char l, int n);
char						*put_width(int len, char *res, char zer, int *n);
char						*ft_itoa_long(long long value);
char						*ft_itoa_u_long(unsigned long long value);
void						ft_get_width_d(long long d, t_p p, int w[2]);
void						ft_get_width_ud(unsigned long long d, t_p p
, int w[2]);
void						ft_get_width_ux(unsigned long long d, t_p p
, int w[2], int base);
void						ft_get_width_uo(unsigned long long d, t_p p
, int w[2], int base);
void						ft_get_width_p(unsigned long long d, t_p p
, int w[2], int base);
long	long				get_nb_casted(t_p p, va_list list);
unsigned	long	long	get_nb_u_casted(t_p p, va_list list);
char						trn(char cond, char c_true, char c_false);
char						*ft_itoa_bas_s(unsigned long long value, int base
, char x);
void						modif_p_for_p(t_p *p);
size_t						ft_strlen_z(const char *s, int nbzer);
char						*ft_strdup_z(const char *s1, int nbzer);
char						ft_bad_uni(unsigned int c);

char						*ft_p_s(t_p p, va_list list, int *n, char *res);
char						*ft_p_s_b(t_p p, va_list list, int *n, char *res);
char						*ft_p_p(t_p p, va_list list, int *n, char *res);
char						*ft_p_d(t_p p, va_list list, int *n, char *res);
char						*ft_p_d_b(t_p p, va_list list, int *n, char *res);
char						*ft_p_i(t_p p, va_list list, int *n, char *res);
char						*ft_p_o(t_p p, va_list list, int *n, char *res);
char						*ft_p_o_b(t_p p, va_list list, int *n, char *res);
char						*ft_p_u(t_p p, va_list list, int *n, char *res);
char						*ft_p_u_b(t_p p, va_list list, int *n, char *res);
char						*ft_p_x(t_p p, va_list list, int *n, char *res);
char						*ft_p_x_b(t_p p, va_list list, int *n, char *res);
char						*ft_p_c(t_p p, va_list list, int *n, char *res);
char						*ft_p_c_b(t_p p, va_list list, int *n, char *res);
char						*ft_p_perc(t_p p, va_list list, int *n, char *res);

char						*ft_p_other(t_p p, int *n, char *res
, unsigned int c);
char						*ft_p_b(t_p p, va_list list, int *n, char *res);

typedef struct				s_typ
{
	char	key;
	char	*(*f)(t_p, va_list, int *n, char *res);
}							t_typ;

static const t_typ g_typ[] = {
	{'s', ft_p_s},
	{'S', ft_p_s_b},
	{'p', ft_p_p},
	{'d', ft_p_d},
	{'D', ft_p_d_b},
	{'i', ft_p_d},
	{'o', ft_p_o},
	{'O', ft_p_o_b},
	{'u', ft_p_u},
	{'U', ft_p_u_b},
	{'x', ft_p_x},
	{'X', ft_p_x_b},
	{'c', ft_p_c},
	{'C', ft_p_c_b},
	{'%', ft_p_perc},
	{'b', ft_p_b},
	{'>', NULL}
};

#endif
