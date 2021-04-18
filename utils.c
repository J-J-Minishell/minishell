#include "minishell.h"

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

int		ft_str_is_printable_ascii(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] >= 32 && s[i] <= 254)
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);

}

int		ft_find_env_var(t_minishell *s, char *var)
{
	int	i;

	i = 0;
	while (s->env[i])
	{
		if (!(ft_strncmp(var, s->env[i], ft_strlen(var))))
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
	j = 0;
	while (s->env[i][j] != '=')
		j++;
	ret = strdup(s->env[i] + j + 1);
	return (ret);
}

void	ft_clean_up(t_minishell *s)
{
	if (line != NULL)
		line = ft_free_ptr(line);
	if (s->home != NULL)
		s->home = ft_free_ptr(s->home);
	if (s->commands != NULL)
		s->commands = ft_free_matrix(s->commands);
	if (s->tokens != NULL)
		s->tokens = ft_free_matrix(s->tokens);
	if (s->history_cmds != NULL)
		s->history_cmds = ft_free_matrix(s->history_cmds);
	s->env = ft_free_matrix(s->env);
	s->blt_cmds = ft_free_matrix(s->blt_cmds);
}

void	*ft_free_matrix(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i] != NULL)
			matrix[i] = ft_free_ptr(matrix[i]);
		i++;
	}
	if (matrix != NULL)
		matrix = ft_free_ptr(matrix);
	return (NULL);
}

void	ft_print_error(t_minishell *s)
{
	printf("Error: %s\n", strerror(errno));
	ft_clean_up(s);
	exit(-1);
}
