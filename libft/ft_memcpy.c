/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 08:26:24 by jgalian-          #+#    #+#             */
/*   Updated: 2019/11/14 10:41:43 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst1;
	unsigned char	*src1;

	dst1 = (unsigned char*)dst;
	src1 = (unsigned char*)src;
	if (n == 0 || dst == src)
		return (dst);
	while (n--)
	{
		*dst1++ = *src1++;
	}
	return (dst);
}
