#include "../../includes/minishell.h"

int	quotes(t_minishell *s, int i, int j)
{
	int		quote;
	char	c;

	c = s->tokens[i][j];
	quote = 1;
	while (s->tokens[i][j] && quote)
	{
		j++;
		if (s->tokens[i][j] == c && check_backslash(s->tokens[i], j))
			quote = 0;
		if (quote)
		{
			if (s->tokens[i][j] == '\\' && ((j > 0 && \
				s->tokens[i][j - 1] == '\\') || s->tokens[i][j + 1] == '$'))
				j++;
			write(s->fd, s->tokens[i] + j, 1);
		}
	}
	return (j);
}

void	check_special_tokens(t_minishell *s)
{
	int		i;
	char	*tmp;

	i = 1;
	while (s->tokens[i])
	{
		if (s->tokens[i][0] == '~' && s->tokens[i][1] == '\0')
		{
			tmp = ft_get_env_var_content(s, "HOME");
			if (tmp)
			{
				ft_free_ptr(s->tokens[i]);
				s->tokens[i] = ft_strdup(tmp);
			}
		}
		i++;
	}
}

int	flag_newline(char *token)
{
	int	i;
	int	newline;

	if (!token)
		return (FALSE);
	newline = FALSE;
	i = 0;
	if (token[i] == '-' && token[i + 1] == 'n')
	{
		newline = TRUE;
		while (token[++i] != '\0')
		{
			if (token[i] != 'n')
			{
				newline = FALSE;
				break ;
			}
		}
	}
	return (newline);
}

void	print_tokens(t_minishell *s, int i)
{
	int	j;

	j = -1;
	while (s->tokens[i][++j])
	{
		if ((s->tokens[i][j] == '"' || s->tokens[i][j] == '\'') && \
			check_backslash(s->tokens[i], j))
			j = quotes(s, i, j);
		else if (s->tokens[i][j] == '\\')
		{
			if (j > 0 && s->tokens[i][j - 1] == '\\' && \
				check_backslash(s->tokens[i], j - 1))
				write(s->fd, s->tokens[i] + j, 1);
		}
		else
			write(s->fd, s->tokens[i] + j, 1);
	}
	if (j && s->tokens[i + 1] && s->tokens[i + 1][0] != '\0')
		write(s->fd, " ", 1);
}

void	cmd_echo(t_minishell *s)
{
	int		i;
	int		newline;

	newline = TRUE;
	if (s->tokens[1])
	{
		check_special_tokens(s);
		i = 0;
		while (flag_newline(s->tokens[++i]))
			newline = FALSE;
		while (s->tokens[i])
		{
			print_tokens(s, i);
			i++;
		}
	}
	if (newline)
		write(s->fd, "\n", 1);
	s->exit_status = 0;
}
