/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:36:03 by jgalian-          #+#    #+#             */
/*   Updated: 2019/12/10 09:25:08 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*aux;

	if (!lst && !del)
		return (NULL);
	aux = lst;
	if (!(new = ft_lstnew(f(aux->content))))
		return (NULL);
	aux = aux->next;
	while (aux)
	{
		if (!(tmp = ft_lstnew(f(aux->content))))
			return (NULL);
		ft_lstadd_back(&new, tmp);
		aux = aux->next;
	}
	return (new);
}
