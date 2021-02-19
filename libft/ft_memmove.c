/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 08:27:09 by jgalian-          #+#    #+#             */
/*   Updated: 2019/11/14 10:57:04 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	size_t			i;

	dst1 = (unsigned char*)dst;
	src1 = (unsigned char*)src;
	i = 0;
	if (len == 0 || dst == src)
		return (dst);
	if (src1 < dst1)
	{
		while (i++ < len)
			dst1[len - i] = src1[len - i];
	}
	else
	{
		while (len--)
			*(dst1++) = *(src1++);
	}
	return (dst);
}
