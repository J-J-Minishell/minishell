#include "minishell.h"

void	ft_process_tokken(t_minishell *s)
{
	int 	i;

	i = 0;
	while (i < 7 && ft_strncmp(s->tokens[0], s->blt_cmds[i], ft_strlen(s->blt_cmds[i])) != 0)
		i++;
	if (i == 0)
		cmd_echo(s);
	else if (i == 1)
		blt_cd(s);
	else if (i == 2)
		blt_pwd(s);
	else if (i == 3)
		blt_export(s);
	else if (i == 4)
		blt_unset(s);
	else if (i == 5)
		blt_env(s);
	else if (i == 6)
	{
		ft_clean_up(s);
		exit(0);
	}
	else
		ft_execute_command(s);
}

int		ft_check_for_pipes(t_minishell *s, int i)
{
	int		j;

	j = -1;
	while (s->commands[i][++j] != '\0')
	{
		if (s->commands[i][j] == '|')
			return (TRUE);
	}
	return (FALSE);
}

int		check_double_redirection_marks(t_minishell *s)
{
	int 	i;

	i = -1;
	while(s->tokens[++i])
	{
		if (s->tokens[i][0] == '>' &&  s->tokens[i][1] == '<')
		{
			printf("-bash: syntax error near unexpected token `<'\n");
			s->exit_status = 258;
			return (TRUE);
		}
		else if ((s->tokens[i][0] == '>' || s->tokens[i][0] == '<') && (s->tokens[i + 1][0] == '>' || s->tokens[i + 1][0] == '<'))
		{
			if (s->tokens[i + 1][0] == '>')
				printf("-bash: syntax error near unexpected token `>'\n");
			else
				printf("-bash: syntax error near unexpected token `<'\n");
			s->exit_status = 258;
			return (TRUE);
		}
	}
}

int		ft_no_pipes(t_minishell *s, int i)
{
	s->tokens = special_split(s->commands[i], ' ');
	if (check_double_redirection_marks(s))
		return (TRUE);
	check_env_var(s);
	check_redirections(s);
	if (s->tokens[0])
	{
		ft_get_path(s);
		ft_process_tokken(s);
		s->tokens = ft_free_matrix(s->tokens);
	}
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

void	get_redirection_marks_apart()
{
	int		i;
	char	*tmp;
	int		len;

	i = -1;
	while (line[++i])
	{
		if ((line[i] == '<' || line[i] == '>') && i > 0 && (line[i - 1] != '<' && line[i - 1] != '>' && line[i - 1] != ' '))
		{
			len = ft_strlen(line);
			tmp = malloc(len + 2);
			ft_memmove(tmp, line, i);
			tmp[i] = ' ';
			ft_memmove(tmp + i + 1, &line[i], len - i);
			tmp[len + 2] = '\0';
			printf("%s\n", tmp);
			free(line);
			line = tmp;
			i = -1;
		}
		else if ((line[i] == '<' || line[i] == '>') && (line[i + 1] != '<' && line[i + 1] != '>' && line[i + 1] != ' '))
		{
			len = ft_strlen(line);
			tmp = malloc(len + 2);
			ft_memmove(tmp, line, i + 1);
			tmp[i + 1] = ' ';
			ft_memmove(tmp + i + 2, &line[i + 1], len - (i + 1));
			tmp[len + 2] = '\0';
			printf("%s\n", tmp);
			free(line);
			line = tmp;
			i = -1;
		}
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

	if (ft_double_semicolon_check(s))
		return ;
	get_redirection_marks_apart();
	s->commands = special_split(line, ';');
	i = -1;
	while (s->commands[++i])
	{
		if (ft_check_for_pipes(s, i))
		{
			s->pipe_commands = special_split(s->commands[i], '|');
			ft_pipes(s);
			s->pipe_commands = ft_free_matrix(s->pipe_commands);
		}
		else
		{
			if (ft_no_pipes(s, i))
				return ;
		}
		if (s->fd != 1)
		close(s->fd);
		s->fd = 1;
	}

	s->commands = ft_free_matrix(s->commands);
	s->command_path = ft_free_ptr(s->command_path);
}
