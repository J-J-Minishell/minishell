#include "../../includes/minishell.h"

int		double_redirection_error(t_minishell *s, int i)
{
	if (i == -1)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (line[i] == '<')
		ft_putstr_fd("-bash: syntax error near unexpected token `<'\n", 2);
	else if (line[i] == '>')
		ft_putstr_fd("-bash: syntax error near unexpected token `>'\n", 2);
	s->exit_status = 258;
	return (TRUE);
}

int		check_double_redirection_marks(t_minishell *s)
{
	int 	i;
	int		flag;

	i = -1;
	flag = 0;
	while(line[++i])
	{
		i += skip_quotes(&line[i]);
		if (!flag && (line[i] == '>' || line[i] == '<'))
			flag = 1;
		else if (flag && line[i] != '>' && line[i] != '<' && line[i] != ' ')
			flag = 0;
		else if (flag && (line[i] == '>' || line[i] == '<'))
		{
			if (line[i] == '>' && (line[i - 1] == '>' || line[i - 1] == '<'))
				flag = 1;
			else
				return (double_redirection_error(s, i));
		}
	}
	if (flag)
		return (double_redirection_error(s, -1));
	return (FALSE);
}

int		ft_double_semicolon_check(t_minishell *s)
{
	int		i;
	int		flag;

	flag = TRUE;
	i = -1;
	while (line[++i])
	{
		i += skip_quotes(&line[i]);
		if (line[i] == ';' && flag == TRUE)
		{
			printf("-bash: syntax error near unexpected token `;'\n");
			s->exit_status = 258;
			return (TRUE);
		}
		else if (line[i] == ';' && flag == FALSE)
			flag = TRUE;
		else if (line[i] == ' ')
			continue ;
		else
			flag = FALSE;
	}
	return (FALSE);
}

void	get_redirection_marks_apart(int i, char *tmp, char *tmp2)
{
	while (line[++i])
	{
		i += skip_quotes(&line[i]);
		if ((line[i] == '<' || line[i] == '>') && i > 0 &&
			(line[i - 1] != '<' && line[i - 1] != '>' && line[i - 1] != ' '))
		{
			tmp = ft_substr(line, 0, i);
			tmp2 = ft_strjoin(" ", &line[i]);
			free(line);
			line = ft_strjoin(tmp, tmp2);
		}
		if ((line[i] == '<' || line[i] == '>') && (line[i + 1] != '<' &&
			line[i + 1] != '>' && line[i + 1] != ' '))
		{
			tmp = ft_substr(line, 0, i + 1);
			tmp2 = ft_strjoin(" ", &line[i + 1]);
			free(line);
			line = ft_strjoin(tmp, tmp2);
		}
		if (tmp)
			tmp = ft_free_ptr(tmp);
		if (tmp2)
			tmp2 = ft_free_ptr(tmp2);
	}
}

/*
** Function ft_process_line() receives the line written on the terminal and
** take care of the steps needed in order to execute all the commands.
** First of all, it splits the line into the different commands separated by
** the ';' character. Then process, one by one, every command.
** For each command follow the next steps. First, it split the command into
** tokens. Then get variable expansion done through the function
** check_env_var(). The next step it would be get all the paths where the
** commands should be searched for. And finally, try to execute the command.
** At the end, function frees the variables that should be freed.
*/
void	ft_process_line(t_minishell *s)
{
	int		i;

	if (ft_double_semicolon_check(s) ||
		check_double_redirection_marks(s))
		return ;
	get_redirection_marks_apart(-1, NULL, NULL);
	s->commands = special_split(line, ';');
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
