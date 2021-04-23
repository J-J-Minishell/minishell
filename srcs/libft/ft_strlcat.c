/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 08:29:45 by jgalian-          #+#    #+#             */
/*   Updated: 2021/04/23 11:39:57 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	i;
	size_t	n;
	size_t	ret;

	dstlen = 0;
	while (dst[dstlen] != '\0' && dstlen < dstsize)
		dstlen++;
	if (dstsize <= (dstlen + 1))
		return (dstlen + ft_strlen(src));
	n = ft_strlen(dst);
	ret = n + ft_strlen(src);
	i = 0;
	while (src[i] != '\0')
	{
		if (n < dstsize - 1)
		{
			dst[n] = src[i];
			n++;
		}
		i++;
	}
	dst[n] = '\0';
	return (ret);
}
