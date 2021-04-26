#include "../../includes/minishell.h"

int incomplete_pipes_error(t_minishell *s, int i, int flag)
{
	if (!flag || (g_ln[i + 1] == '\0' || g_ln[i + 1] == '|'))
	{
		ft_putstr_fd("-bash: syntax error near unexpected token `|'\n", 2);
		s->exit_status = 258;
		return (1);
	}
	else if (g_ln[i + 1] == ';')
	{
		ft_putstr_fd("-bash: syntax error near unexpected token `;'\n", 2);
		s->exit_status = 258;
		return (1);
	}
	return (0);
}

int	check_incomplete_pipes(t_minishell *s)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (g_ln[++i])
	{
		i += skip_quotes(&g_ln[i]);
		if (g_ln[i] == '|')
		{
			while (g_ln[i + 1] == ' ')
				i++;
			if (incomplete_pipes_error(s, i, flag))
				return (1);
			flag = 0;
		}
		else
		{	
			if (g_ln[i] == ';')
				flag = 0;
			else if (g_ln[i] != ' ')
				flag = 1;
		}
	}
	return (0);
}

int	double_redirection_error(t_minishell *s, int i)
{
	if (i == -1)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (g_ln[i] == '<')
		ft_putstr_fd("-bash: syntax error near unexpected token `<'\n", 2);
	else if (g_ln[i] == '>')
		ft_putstr_fd("-bash: syntax error near unexpected token `>'\n", 2);
	s->exit_status = 258;
	return (TRUE);
}

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
