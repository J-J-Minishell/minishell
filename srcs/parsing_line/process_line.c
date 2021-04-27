#include "../../includes/minishell.h"

int	open_quotes(int i, int double_q, int single_q)
{
	while (g_ln[i] && (double_q || single_q))
	{
		if (g_ln[i] == '"' && check_backslash(g_ln, i))
			double_q = 0;
		else if (g_ln[i] == '\'' && check_backslash(g_ln, i))
			single_q = 0;
		i++;
	}
	if (double_q || single_q)
	{
		ft_putstr_fd("-bash: open quotes error\n", 2);
		return (-1);
	}
	return (i);
}

int	check_open_quotes()
{
	int	i;
	int	double_q;
	int	single_q;

	i = 0;
	double_q = 0;
	single_q = 0;
	while (g_ln[i])
	{
		while (g_ln[i] && !double_q && !single_q)
		{
			if (g_ln[i] == '"' && check_backslash(g_ln, i))
				double_q = 1;
			else if (g_ln[i] == '\'' && check_backslash(g_ln, i))
				single_q = 1;
			i++;
		}
		i = open_quotes(i, double_q, single_q);
		if (i == -1)
			return (1);
		double_q = 0;
		single_q = 0;
	}
	return (0);
}

void	get_redirection_marks_apart(int i, char *tmp, char *tmp2)
{
	while (g_ln[++i])
	{
		i += skip_quotes(&g_ln[i]);
		if ((g_ln[i] == '<' || g_ln[i] == '>') && i > 0 && g_ln[i - 1] != '\\'
			&& g_ln[i - 1] != '<' && g_ln[i - 1] != '>' && g_ln[i - 1] != ' ')
		{
			tmp = ft_substr(g_ln, 0, i);
			tmp2 = ft_strjoin(" ", &g_ln[i]);
			free(g_ln);
			g_ln = ft_strjoin(tmp, tmp2);
		}
		if ((g_ln[i] == '<' || g_ln[i] == '>') && (g_ln[i + 1] != '<' && \
			g_ln[i + 1] != '>' && g_ln[i + 1] != ' '))
		{
			tmp = ft_substr(g_ln, 0, i + 1);
			tmp2 = ft_strjoin(" ", &g_ln[i + 1]);
			free(g_ln);
			g_ln = ft_strjoin(tmp, tmp2);
		}
		if (tmp)
			tmp = ft_free_ptr(tmp);
		if (tmp2)
			tmp2 = ft_free_ptr(tmp2);
	}
}

void	ft_process_line(t_minishell *s)
{
	int		i;

	if (ft_double_semicolon_check(s) || check_open_quotes() || \
		check_double_redirection_marks(s) || check_incomplete_pipes(s))
		return ;
	get_redirection_marks_apart(-1, NULL, NULL);
	s->commands = special_split(g_ln, ';');
	i = -1;
	while (s->commands[++i])
	{
		ft_process_command(s, i);
		if (s->fd != 1)
			close(s->fd);
		if (s->fdi != 0)
			close(s->fdi);
		s->fd = 1;
		s->fdi = 0;
		s->command_path = ft_free_ptr(s->command_path);
	}
	s->commands = ft_free_matrix(s->commands);
}
