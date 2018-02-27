/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:25:19 by emarin            #+#    #+#             */
/*   Updated: 2017/12/17 13:57:14 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list *start;

	if (alst != NULL)
	{
		if (*alst == NULL)
		{
			*alst = new;
			return ;
		}
		start = *alst;
		while ((*alst)->next != 0)
			(*alst) = (*alst)->next;
		(*alst)->next = new;
		(*alst) = start;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlst;

	if (lst == NULL)
		return (NULL);
	newlst = f(lst);
	lst = lst->next;
	while (lst != NULL)
	{
		ft_lstpushback(&newlst, f(lst));
		lst = lst->next;
	}
	return (newlst);
}
