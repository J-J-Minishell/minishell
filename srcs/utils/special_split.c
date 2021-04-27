#include "../../includes/minishell.h"

int	skip_char(char *s, char c, int i)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	count_words(char *s, char c, int w)
{
	int		i;
	int		quote;
	char	char_quote;

	i = 0;
	i = skip_char(s, c, i);
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '"' || s[i] == '\'') && check_backslash(s, i))
		{
			quote = 1;
			char_quote = s[i];
		}
		else if (quote && s[i] == char_quote && check_backslash(s, i))
			quote = 0;
		if (s[i] == c && !quote && check_backslash(s, i))
		{
			i = skip_char(s, c, i);
			w += (s[i] != '\0');
		}
		else
			i++;
	}
	return (w);
}

static int	count_chars(char *s, char c)
{
	int		i;
	int		quote;
	char	char_quote;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '"' || s[i] == '\'') && check_backslash(s, i))
		{
			quote = 1;
			char_quote = s[i];
		}
		else if (quote && s[i] == char_quote && check_backslash(s, i))
			quote = 0;
		if (s[i] == c && !quote && check_backslash(s, i))
			break ;
		i++;
	}
	return (i);
}

void	*clean(char **out, int w)
{
	while (w)
	{
		free(out[w]);
		w--;
	}
	free(out);
	return (NULL);
}

char	**special_split(char *s, char c)
{
	int		wordcount;
	int		w;
	char	**out;

	if (!s)
		return (NULL);
	wordcount = count_words(s, c, 1);
	out = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!out)
		return (NULL);
	w = 0;
	while (w < wordcount)
	{
		while (*s != '\0' && *s == c)
			s++;
		out[w] = ft_substr(s, 0, count_chars(s, c));
		if (!out[w])
			return (clean(out, w - 1));
		w++;
		s = s + count_chars(s, c);
	}
	out[w] = NULL;
	return (out);
}
