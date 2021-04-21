#include "../../includes/minishell.h"

int		quotes(t_minishell *s, int i, int j)
{
	int		single_q;
	int		double_q;

	double_q = (s->tokens[i][j] == '"');
	single_q = (s->tokens[i][j] == '\'');
	while (s->tokens[i][j] && (double_q || single_q))
	{
		j++;
		double_q *= (s->tokens[i][j] != '"');
		single_q *= (s->tokens[i][j] != '\'');
		if (double_q || single_q)
		{
			if (s->tokens[i][j] == '\\' && j > 0 && s->tokens[i][j - 1] == '\\')
				j++;
			write(s->fd, s->tokens[i] + j, 1);
		}
	}
	return (j);
}

int		flag_newline(t_minishell *s)
{
	int i;

	i = 1;
	while (s->tokens[i] && s->tokens[i][0] != '\0' &&
		ft_strncmp(s->tokens[i], "-n", ft_strlen(s->tokens[i])) == 0)
		i++;
	return (i);
}

void	check_special_tokens(t_minishell *s)
{
	int		i;
	char	*tmp;
	int		j;

	i = 1;
	while (s->tokens[i])
	{
		if (s->tokens[i][0] == '~' && s->tokens[i][1] == '\0')
		{
			//j = ft_find_env_var(s, "HOME");
			//printf("%i\n", j);
			tmp = ft_get_env_var_content(s, "HOME");
			//printf("hola");
			ft_free_ptr(s->tokens[i]);
			s->tokens[i] = ft_strdup(tmp);
		}
		i++;
	}
}

void	cmd_echo(t_minishell *s)
{
	int		i;
	int		j;
	int		newline;
	int		counterbar;

	check_special_tokens(s);
	counterbar = FALSE;
	i = flag_newline(s);
	newline = i > 1 ? 0 : 1;
	while (s->tokens[i])
	{
		j = 0;
		while (s->tokens[i][j])
		{
			if (s->tokens[i][j] == '"' || s->tokens[i][j] == '\'')
				j = quotes(s, i, j);
			else
			{
				if (s->tokens[i][j] == '\\')
					counterbar = TRUE;
				if (counterbar)
				{
					counterbar = FALSE;
					j++;
				}
				write(s->fd, s->tokens[i] + j, 1);
			}
			j++;
		}
		if (j && s->tokens[i + 1])
			write(s->fd, " ", 1);
		i++;
	}
	if (newline)
		write(s->fd, "\n", 1);
	s->exit_status = 0;
}
