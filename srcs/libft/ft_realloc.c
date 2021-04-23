/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 23:17:27 by jgalian-          #+#    #+#             */
/*   Updated: 2021/04/23 11:43:16 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*ret;
	size_t	old_size;

	if (ptr == NULL)
		return (ret = malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		ret = malloc(size);
		if (!size)
			return (NULL);
		old_size = sizeof(ptr);
		ft_memcpy(ret, ptr, old_size);
		free(ptr);
		return (ret);
	}
}
