/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:41:00 by jgalian-          #+#    #+#             */
/*   Updated: 2019/11/29 12:12:41 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*sub;
	size_t	i;

	str = (char *)s;
	i = 0;
	if (str == NULL)
		return (NULL);
	if (!(sub = (char *)malloc(len + 1)))
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (str[i] != '\0' && i < len)
		{
			sub[i] = str[i + start];
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}
