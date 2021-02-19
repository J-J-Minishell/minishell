/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 08:30:01 by jgalian-          #+#    #+#             */
/*   Updated: 2019/11/15 15:23:26 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == '\0' && c == '\0')
		return (str);
	return (NULL);
}
