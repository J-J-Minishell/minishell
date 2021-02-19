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

void	cmd_echo(t_minishell *s)
{
	int		i;
	int		j;

	i = 1;
	while (s->tokens[i])
	{
		j = 0;
		while (s->tokens[i][j])
		{
			if (s->tokens[i][j] == '"' || s->tokens[i][j] == '\'')
				j = quotes(s, i, j);
			else
				write(1, s->tokens[i] + j, 1);
			j++;
		}
		if (j)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
