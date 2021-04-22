#include "../../includes/minishell.h"
int	skip_char(char *s, char c, int i)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	count_words(char *s, char c)
{
	int	i;
	int	double_q;
	int	single_q;
	int	w;

	i = 0;
	w = 1;
	i = skip_char(s, c, i);
	double_q = 0;
	single_q = 0;
	while (s[i])
	{
		if (s[i] == '"' && check_backslash(s, i))
			double_q = (double_q != 1);
		else if (s[i] == '\'' && check_backslash(s, i))
			single_q = (single_q != 1);
		if (s[i] == c && !double_q && !single_q && check_backslash(s, i))
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
	int	i;
	int	double_q;
	int	single_q;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && check_backslash(s, i))
			double_q = (double_q != 1);
		else if (s[i] == '\'' && check_backslash(s, i))
			single_q = (single_q != 1);
		if (s[i] == c && !double_q && !single_q && check_backslash(s, i))
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
	wordcount = count_words(s, c);
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
