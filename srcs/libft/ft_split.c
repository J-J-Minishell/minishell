/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 08:16:02 by jgalian-          #+#    #+#             */
/*   Updated: 2021/04/23 11:42:41 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_next_word(const char *s, char c)
{
	while (*s != '\0' && *s == c)
		s++;
	return ((char *)s);
}

static int	ft_count_words(const char *s, char c)
{
	int		w;
	int		i;

	i = 0;
	w = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		w++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (w);
}

static int	ft_count_chars(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_clean(char **out, int w)
{
	while (w)
	{
		free(out[w]);
		w--;
	}
	free(out);
}

char	**ft_split(char const *s, char c)
{
	int		wordcount;
	int		w;
	char	**out;

	if (!s)
		return (NULL);
	wordcount = ft_count_words(s, c);
	out = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!out)
		return (NULL);
	w = 0;
	while (w < wordcount)
	{
		s = ft_next_word(s, c);
		out[w] = ft_substr(s, 0, ft_count_chars(s, c));
		if (!out)
		{
			ft_clean(out, w - 1);
			return (NULL);
		}
		w++;
		s = s + ft_count_chars(s, c);
	}
	out[w] = NULL;
	return (out);
}
