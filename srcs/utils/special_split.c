#include "../../includes/minishell.h"

static char	*next_word(const char *s, char c)
{
	while (*s != '\0' && *s == c)
		s++;
	return ((char*)s);
}

static int	count_words(const char *s, char c)
{
	int i;
	int double_q;
	int single_q;
	int w;

	i = 0;
	w = 1;
	while (s[i] && s[i] == c)
		i++;
	double_q = 0;
	single_q = 0;
	while (s[i])
	{
		if (s[i] == '"' && s[i - 1] != '\\')
			double_q = (double_q != 1);
		else if (s[i] == '\'' && s[i - 1] != '\\')
			single_q = (single_q != 1);
		if (s[i] == c && !double_q && !single_q && s[i - 1] != '\\')
		{
			w++;
			while (s[i] && s[i] == c)
				i++;
			w -= (s[i] == '\0');
		}
		else
			i++;
	}
	return (w);
}

static int	count_chars(const char *s, char c)
{
	int		i;
	int double_q;
	int single_q;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && s[i - 1] != '\\')
			double_q = (double_q != 1);
		else if (s[i] == '\'' && s[i - 1] != '\\')
			single_q = (single_q != 1);
		if (s[i] == c && !double_q && !single_q && s[i - 1] != '\\')
			break;
		i++;
	}
	return (i);
}

static void	clean(char **out, int w)
{
	while (w)
	{
		free(out[w]);
		w--;
	}
	free(out);
}

char		**special_split(char const *s, char c)
{
	int		wordcount;
	int		w;
	char	**out;

	if (!s)
		return (NULL);
	wordcount = count_words(s, c);
	if (!(out = (char**)malloc(sizeof(char*) * (wordcount + 1))))
		return (NULL);
	w = 0;
	while (w < wordcount)
	{
		s = next_word(s, c);
		if (!(out[w] = ft_substr(s, 0, count_chars(s, c))))
		{
			clean(out, w - 1);
			return (NULL);
		}
		w++;
		s = s + count_chars(s, c);
	}
	out[w] = NULL;
	return (out);
}
