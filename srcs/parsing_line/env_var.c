#include "../../includes/minishell.h"

/*
** This function receives the memory address where the environment variable
** starts (just after the '$' character) and obtains the lenght of the
** variable's content.
** It starts checking if the first position is the '=' character and set a flag
** to define where to start.
** Then, starts checking each character until something different fron '_'
** or alfanumeric character is founded. The counter is increased with each
** character checked. And add 1 more at the end.
** Just after that, the function copies variable's name to a temporal string
** through ft_substr() function wich use malloc().
*/

int		len_env_var(t_minishell *s, char *str)
{
	int		i;
	int		len;
	char	*name;
	char	*tmp;

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
	while (s->tokens[i][j] && s->tokens[i][j] != '"' && s->tokens[i][j] != '\'' && s->tokens[i][j] != ' ' && s->tokens[i][j] != '$' && s->tokens[i][j] != '=')
		j++;
	token = ft_strjoin(tmp, tmp2 = ft_substr(s->tokens[i], j, ft_strlen(s->tokens[i]) - j));
	tmp = ft_free_ptr(tmp);
	tmp2 = ft_free_ptr(tmp2);
	s->tokens[i] = ft_free_ptr(s->tokens[i]);
	s->tokens[i] = token;
}

/*
** This function receives (in addition to the struct) the token number, and the
** number that corresponds to the '$' char position inside the token. And after
** get the substitution done, it returns a number that stands for the position
** where the caller function (check_env_var()) should continue searching for
** more variables to expand.
** First the function calls to len_env_var() that returns the name of the
** variable to be expanded plus one. And also set a varible accesible through
** the struct, with a pointer to the variable content.
** Then, there is an if (for regular variables, those made of alfanumeric
** characters or '_'), and and else (for the rest).
** Inside the if,
*/

int		replace_env_var(t_minishell *s, int i, int j)
{
	char	*token;
	char	*tmp;
	int		len;
	char	*tmp2;

	len = len_env_var(s, &s->tokens[i][j + 1]);
	if (len == 0 && s->tokens[i][j + 1] == '?')
	{
		len = 2;
		s->env_address = ft_itoa(s->exit_status);
	}
	if (len)
	{
		tmp = ft_strjoin((tmp2 = ft_substr(s->tokens[i], 0, j)), s->env_address);
		tmp2 = ft_free_ptr(tmp2);
		token = ft_strjoin(tmp, (tmp2 = ft_substr(s->tokens[i], j + len, ft_strlen(s->tokens[i] + j + len))));
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

/*
** This function checks every token serching for environment variables to be
** replaced whit their value. If environment variable is between single quotes
** it is not replaced.
** It works checking each character in the token. If a quote is located a flag
** is set to show if they are opened or closed. Also check for '$' char. If one
** is located beeing followed by alfanumeric characters, function calls
** replace_env_var() function to get the replacement done (except if the
** '$' character was inside a single quote space or the '$' character is not
** preceded by '\' character that would remove the '$' special meaning).
** Finally, function should freed s->env_address variable allocated inside of
** len_env_var function.
*/

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
				double_q = !single_q && !double_q ? 1 : 0;
			else if (s->tokens[i][j] == '\'')
				single_q = !double_q && !single_q ? 1 : 0;
			else if (s->tokens[i][j] == '$' && (ft_isalpha(s->tokens[i][j + 1]) ||  s->tokens[i][j + 1] == '_' || s->tokens[i][j + 1] == '?'
				|| s->tokens[i][j + 1] == '"') && !single_q && !ft_counterbar_before_expansion(s, i, j))
			{
				j += replace_env_var(s, i, j);
				s->env_address = ft_free_ptr(s->env_address);
			}
			j++;
		}
		i++;
	}
	s->exit_status = 0;
}

int			ft_counterbar_before_expansion(t_minishell *s, int i, int j)
{
	int		counterbar;

	counterbar = 0;
	while (j > 0 && s->tokens[i][--j] == '\\')
		counterbar++;
	if (counterbar % 2)
		return (TRUE);
	return (FALSE);
}
