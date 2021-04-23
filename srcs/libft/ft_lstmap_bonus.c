/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <jgalian-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:36:03 by jgalian-          #+#    #+#             */
/*   Updated: 2021/04/23 11:47:04 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*aux;

	if (!lst && !del)
		return (NULL);
	aux = lst;
	new = ft_lstnew(f(aux->content));
	if (!new)
		return (NULL);
	aux = aux->next;
	while (aux)
	{
		tmp = ft_lstnew(f(aux->content));
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&new, tmp);
		aux = aux->next;
	}
	return (new);
}
