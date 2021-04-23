#include "../../includes/minishell.h"

int	len_env_var(t_minishell *s, char *str)
{
	int		i;
	int		len;
	char	*name;
	char	*tmp;

	if (str[0] == '?')
	{
		s->env_address = ft_itoa(s->exit_status);
		return (2);
	}
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	len = i + 1;
	tmp = ft_substr(str, 0, i);
	name = ft_strjoin(tmp, "=");
	tmp = ft_free_ptr(tmp);
	i = ft_find_env_var(s, name);
	if (i >= 0)
		s->env_address = ft_strdup(s->env[i] + len);
	name = ft_free_ptr(name);
	if (s->env_address)
		return (len);
	return (0);
}

void	wrong_env_var(t_minishell *s, int i, int j)
{
	char	*token;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(s->tokens[i], 0, j);
	j++;
	while (s->tokens[i][j] && s->tokens[i][j] != '"' && s->tokens[i][j] != '\'' && \
	s->tokens[i][j] != ' ' && s->tokens[i][j] != '$' && s->tokens[i][j] != '=')
		j++;
	tmp2 = ft_substr(s->tokens[i], j, ft_strlen(s->tokens[i]) - j);
	token = ft_strjoin(tmp, tmp2);
	tmp = ft_free_ptr(tmp);
	tmp2 = ft_free_ptr(tmp2);
	s->tokens[i] = ft_free_ptr(s->tokens[i]);
	s->tokens[i] = token;
}

int	replace_env_var(t_minishell *s, int i, int j)
{
	char	*token;
	char	*tmp;
	int		len;
	char	*tmp2;

	len = len_env_var(s, &s->tokens[i][j + 1]);
	if (len)
	{
		tmp2 = ft_substr(s->tokens[i], 0, j);
		tmp = ft_strjoin(tmp2, s->env_address);
		tmp2 = ft_free_ptr(tmp2);
		tmp2 = ft_substr(s->tokens[i], j + len, \
		ft_strlen(s->tokens[i] + j + len));
		token = ft_strjoin(tmp, tmp2);
		tmp2 = ft_free_ptr(tmp2);
		tmp = ft_free_ptr(tmp);
		s->tokens[i] = ft_free_ptr(s->tokens[i]);
		s->tokens[i] = token;
		return (ft_strlen(s->env_address) - 1);
	}
	else
		wrong_env_var(s, i, j);
	return (-1);
}

int	find_env_var(t_minishell *s, int single_q, int i, int j)
{
	if (s->tokens[i][j] == '$' && (ft_isalpha(s->tokens[i][j + 1]) || \
		s->tokens[i][j + 1] == '_' || s->tokens[i][j + 1] == '?' || \
		s->tokens[i][j + 1] == '"') && !single_q && \
		check_backslash(s->tokens[i], j))
	{
		j += replace_env_var(s, i, j);
		s->env_address = ft_free_ptr(s->env_address);
	}
	return (j);
}

void	check_env_var(t_minishell *s)
{
	int		i;
	int		j;
	int		single_q;
	int		double_q;

	i = 0;
	while (s->tokens[i])
	{
		j = 0;
		double_q = 0;
		single_q = 0;
		while (s->tokens[i][j])
		{
			if (s->tokens[i][j] == '"')
				double_q = (!single_q && !double_q);
			else if (s->tokens[i][j] == '\'')
				single_q = (!double_q && !single_q);
			j = find_env_var(s, single_q, i, j);
			j++;
		}
		i++;
	}
	s->exit_status = 0;
}
