/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:08:23 by jgalian-          #+#    #+#             */
/*   Updated: 2019/11/23 13:58:38 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str3;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(str3 = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i] != '\0')
	{
		str3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str3[i] = s2[j];
		i++;
		j++;
	}
	str3[i] = '\0';
	return (str3);
}
