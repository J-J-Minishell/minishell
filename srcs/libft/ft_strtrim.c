/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:46:42 by jgalian-          #+#    #+#             */
/*   Updated: 2021/04/23 11:37:52 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strbacktrimlen(char *string1, const char *set)
{
	int		len;
	int		j;

	j = 0;
	len = 0;
	while (string1[len])
		len++;
	while (len > 0)
	{
		while (set[j] != '\0')
		{
			if (string1[len - 1] == set[j])
			{
				len--;
				j = 0;
			}
			else
				j++;
		}
		return (len);
	}
	return (0);
}

static char	*ft_strfronttrim(char *string1, const char *set)
{
	int		j;

	j = 0;
	while (set[j] != '\0')
	{
		if (*string1 == set[j])
		{
			string1++;
			j = 0;
		}
		else
			j++;
	}
	return (string1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*str2;
	char	*str1;

	str1 = (char *)s1;
	if (!s1 || !set)
		return (0);
	str1 = ft_strfronttrim(str1, set);
	if (!str1)
		return (ft_strdup(s1));
	len = ft_strbacktrimlen(str1, set);
	str2 = (char *)malloc(len + 1);
	if (!str2)
		return (0);
	i = 0;
	while (i < len)
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
