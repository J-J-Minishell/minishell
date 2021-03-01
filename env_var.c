#include "minishell.h"

int		len_env_var(t_minishell *s, char *str)
{
	int		i;
	int		len;
	char	*name;
	char	*temp;

	i = str[0] == '=' ? 1 : 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	len = i + 1;
	temp = str[0] == '=' ? ft_substr(str, 1, i) : ft_substr(str, 0, i);
	name = ft_strjoin(temp, "=");
	temp = ft_free_ptr(temp);
	i = ft_find_env_var(s, name);
	if (i >= 0)
		s->env_address = ft_strdup(s->env[i] + len);
	name = ft_free_ptr(name);
	if (s->env_address)
		return (len);
	return (0);
}

int		replace_env_var(t_minishell *s, int i, int j)
{
	char	*token;
	char	*tmp;
	int		len;
	char	*temp2;

	len = len_env_var(s, &s->tokens[i][j + 1]);
	if (len)
	{
		tmp = ft_strjoin((temp2 = ft_substr(s->tokens[i], 0, j)), s->env_address);
		temp2 = ft_free_ptr(temp2);
		token = ft_strjoin(tmp, (temp2 = ft_substr(s->tokens[i], j + len, ft_strlen(s->tokens[i]))));
		temp2 = ft_free_ptr(temp2);
		tmp = ft_free_ptr(tmp);
		s->tokens[i] = ft_free_ptr(s->tokens[i]);
		s->tokens[i] = token;
		return (ft_strlen(s->env_address) - 1);
	}
	else
	{
		tmp = ft_substr(s->tokens[i], 0, j);
		j++;
		while (s->tokens[i][j] && s->tokens[i][j] != '"' && s->tokens[i][j] != '\'' && s->tokens[i][j] != ' ' && s->tokens[i][j] != '$')
			j++;
		token = ft_strjoin(tmp, ft_substr(s->tokens[i], j, ft_strlen(s->tokens[i])));
		tmp = ft_free_ptr(tmp);
		s->tokens[i] = ft_free_ptr(s->tokens[i]);
		s->tokens[i] = token;
		return (-1);
	}
}

void	check_env_var(t_minishell *s)
{
	int		i;
	int		j;
	int		single_q;
	int		double_q;

	i = 1;
	while (s->tokens[i])
	{
		j = 0;
		double_q = 0;
		single_q = 0;
		while (s->tokens[i][j])
		{
			if (s->tokens[i][j] == '"')
				double_q = !single_q && !double_q ? 1 : 0;
			else if (s->tokens[i][j] == '\'')
				single_q = !double_q && !single_q ? 1 : 0;
			else if (s->tokens[i][j] == '$' && (ft_isalnum(s->tokens[i][j + 1]) || s->tokens[i][j + 1] == '=')
				&& !single_q && (j == 0 || s->tokens[i][j - 1] != '\\'))
			{
				j += replace_env_var(s, i, j);
				s->env_address = ft_free_ptr(s->env_address);
			}
			j++;
		}
		i++;
	}
}
