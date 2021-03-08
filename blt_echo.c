#include "minishell.h"

int		quotes(t_minishell *s, int i, int j)
{
	int		single_q;
	int		double_q;

	double_q = s->tokens[i][j] == '"' ? 1 : 0;
	single_q = s->tokens[i][j] == '\'' ? 1 : 0;
	while (s->tokens[i][j] && (double_q || single_q))
	{
		j++;
		double_q = s->tokens[i][j] == '"' ? 0 : double_q;
		single_q = s->tokens[i][j] == '\'' ? 0 : single_q;

		if (double_q || single_q)
			write(1, s->tokens[i] + j, 1);
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

void	cmd_echo(t_minishell *s)
{
	int		i;
	int		j;
	int		newline;

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
				if (s->tokens[i][j + 1] == '?')
				{
					ft_putnbr_fd(s->exit_status, 1);
					break ;
				}
				else
					write(1, s->tokens[i] + j, 1);
			}
			j++;
		}
		if (j && s->tokens[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}
