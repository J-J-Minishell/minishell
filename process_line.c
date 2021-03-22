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

void	delete_redirections(t_minishell *s, int redirections, int i)
{
	char	**tokens;
	int		len;
	int		j;

	len = i - (redirections * 2);
	if (!(tokens = (char **)malloc(sizeof(char *) * (len + 1))))
		ft_print_error(s);
	i = 0;
	j = 0;
	while (s->tokens[i])
	{
		if (!ft_strncmp(s->tokens[i], ">", 2) || !ft_strncmp(s->tokens[i], ">>", 3))
			i += 2;
		else
		{
			tokens[j] = ft_strdup(s->tokens[i]);
			j++;
			i++;
		}
	}
	tokens[j] = NULL;
	s->tokens = ft_free_matrix(s->tokens);
	s->tokens = tokens;
}

void	delete_in_redirections(t_minishell *s, int redirections, int i)
{
	char	**tokens;
	int		len;
	int		j;

	len = i - (redirections * 2);
	if (!(tokens = (char **)malloc(sizeof(char *) * (len + 1))))
		ft_print_error(s);
	i = 0;
	j = 0;
	while (s->tokens[i])
	{
		if (!ft_strncmp(s->tokens[i], "<", 2))
			i += 2;
		else
		{
			tokens[j] = ft_strdup(s->tokens[i]);
			j++;
			i++;
		}
	}
	tokens[j] = NULL;
	s->tokens = ft_free_matrix(s->tokens);
	s->tokens = tokens;
}

void	check_redirections(t_minishell *s)
{
	int		i;
	int		redirections;

	redirections = 0;
	i = 0;
	while (s->tokens[i])
	{
		if (ft_strncmp(s->tokens[i], ">", 2) == 0)
		{
			s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			redirections++;
		}
		else if (ft_strncmp(s->tokens[i], ">>", 3) == 0)
		{
			s->fd = open(s->tokens[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			redirections++;
		}
		i++;
		if (s->fd != 1 && s->tokens[i] && (!ft_strncmp(s->tokens[i], ">", 2) ||
			!ft_strncmp(s->tokens[i], ">>", 3)))
			close(s->fd);
	}
	if (redirections)
		delete_redirections(s, redirections, i);
}

void	check_in_redirections(t_minishell *s)
{
	int		i;
	int		redirections;

	redirections = 0;
	i = 0;
	while (s->tokens[i])
	{
		if (ft_strncmp(s->tokens[i], "<", 2) == 0)
		{
			s->fdi = open(s->tokens[i + 1], O_RDONLY, 0);
			redirections++;
		}
		i++;
	}
	if (redirections)
		delete_in_redirections(s, redirections, i);
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
** To get closed, function frees the variables that should be freed.
*/

void	ft_process_line(t_minishell *s)
{
	int 	i;

	s->commands = special_split(s->line, ';');
	i = 0;
	while (s->commands[i])
	{
		s->tokens = special_split(s->commands[i], ' ');
		check_env_var(s);
		ft_get_path(s);
		check_in_redirections(s);
		check_redirections(s);
		ft_process_tokken(s);
		if (s->fd != 1)
			close(s->fd);
		s->fd = 1;
		s->command_path = ft_free_ptr(s->command_path);
		s->path = ft_free_ptr(s->path);
		s->tokens = ft_free_matrix(s->tokens);
		i++;
	}
	s->commands = ft_free_matrix(s->commands);
}

