/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:23:49 by malaoui           #+#    #+#             */
/*   Updated: 2019/10/21 23:43:25 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *holder;

	new = ft_lstnew(f(lst->content));
	if (!new)
		ft_lstdelone(new, del);
	holder = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = ft_lstnew(f(lst->content))))
			ft_lstclear(&holder, del);
		new = new->next;
		lst = lst->next;
	}
	return (holder);
}
