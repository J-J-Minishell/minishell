#include "../../includes/minishell.h"

int		skip_quotes(char *s)
{
	int		i;
	int		d_quotes;
	int		s_quotes;

	i = 0;
	d_quotes = (s[i] == '"');
	s_quotes = (s[i] == '\'');
	while ((d_quotes || s_quotes) && s[++i])
	{
		if (d_quotes)
			d_quotes *= (s[i] != '"');
		else
			d_quotes = (s[i] == '"');
		if (s_quotes)
			s_quotes *= (s[i] != '\'');
		else
			s_quotes = (s[i] == '\'');
	}
	return (i);
}

char	**add_new_pos_matrix(char **matrix, char *new)
{
	char	**tmp;
	int		i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (matrix && matrix[i])
	{
		tmp[i] = ft_strdup(matrix[i]);
		i++;
	}
	tmp[i] = ft_strdup(new);
	tmp[i + 1] = NULL;
	if (matrix)
		matrix = ft_free_matrix(matrix);
	return (tmp);
}

char	**cpy_matrix(char **matrix, int size)
{
	char	**tmp;
	int		i;

	if (!matrix)
		return (NULL);
	if (!(tmp = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (matrix[i] && i < size)
	{
		tmp[i] = ft_strdup(matrix[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int		ft_find_env_var(t_minishell *s, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (s->env[i])
	{
		if (!(ft_strncmp(var, s->env[i], len)))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_get_env_var_content(t_minishell *s, char *var)
{
	int		i;
	int		j;
	char	*ret;

	i = ft_find_env_var(s, var);
	if (i == -1)
		return (NULL);
	j = 0;
	while (s->env[i][j] != '=')
		j++;
	ret = strdup(s->env[i] + j + 1);
	return (ret);
}
