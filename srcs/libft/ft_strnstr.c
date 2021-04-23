/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 08:31:04 by jgalian-          #+#    #+#             */
/*   Updated: 2021/04/23 11:38:21 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	if (*src == '\0')
		return ((char *)dst);
	j = 0;
	while (dst[j] != '\0' && j < len)
	{
		i = 0;
		while (src[i] == dst[j + i] && j + i < len)
		{
			if (src[i + 1] == '\0')
			{
				return ((char *)dst + j);
			}
			i++;
		}
		j++;
	}
	return (0);
}
