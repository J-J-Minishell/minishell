#include "../../includes/minishell.h"

int	check_double_redirection_marks(t_minishell *s)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (g_ln[++i])
	{
		i += skip_quotes(&g_ln[i]);
		if (!flag && (g_ln[i] == '>' || g_ln[i] == '<') && i > 0
			&& g_ln[i - 1] != '\\')
			flag = 1;
		else if (flag && g_ln[i] != '>' && g_ln[i] != '<' && g_ln[i] != ' ')
			flag = 0;
		else if (flag && (g_ln[i] == '>' || g_ln[i] == '<'))
		{
			if (g_ln[i] == '>' && (g_ln[i - 1] == '>' || g_ln[i - 1] == '<'))
				flag = 1;
			else
				return (double_redirection_error(s, i));
		}
	}
	if (flag)
		return (double_redirection_error(s, -1));
	return (FALSE);
}

int	ft_double_semicolon_check(t_minishell *s)
{
	int		i;
	int		flag;

	flag = TRUE;
	i = -1;
	while (g_ln[++i])
	{
		i += skip_quotes(&g_ln[i]);
		if (g_ln[i] == ';' && flag == TRUE)
		{
			printf("-bash: syntax error near unexpected token `;'\n");
			s->exit_status = 258;
			return (TRUE);
		}
		else if (g_ln[i] == ';' && flag == FALSE)
			flag = TRUE;
		else if (g_ln[i] == ' ')
			continue ;
		else
			flag = FALSE;
	}
	return (FALSE);
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

int	check_incomplete_pipes(t_minishell *s)
{
	int		i;

	i = -1;
	while (g_ln[++i])
	{
		i += skip_quotes(&g_ln[i]);
		if (g_ln[i] == '|')
		{
			while (g_ln[i + 1] == ' ')
				i++;
			if (g_ln[i + 1] == '\0' || g_ln[i + 1] == '|')
			{
				printf("-bash: syntax error near unexpected token `|'\n");
				s->exit_status = 258;
				return (1);
			}
			else if (g_ln[i + 1] == ';')
			{
				printf("-bash: syntax error near unexpected token `;'\n");
				s->exit_status = 258;
				return (1);
			}
		}
	}
	return (0);
}

void	ft_process_line(t_minishell *s)
{
	int		i;

	if (ft_double_semicolon_check(s) || \
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
		s->fd = 1;
		s->command_path = ft_free_ptr(s->command_path);
	}
	s->commands = ft_free_matrix(s->commands);
}
