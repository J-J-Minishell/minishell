#include "../../includes/minishell.h"

void	no_blt(t_minishell *s)
{
	struct stat	st;

	if (stat(s->command_path, &st))
	{
		ft_putstr_fd("-bash_no_blt: ", 2);
		ft_putstr_fd(error_backslash_var(s, s->tokens[0]), 2);
		if (ft_strchr(s->tokens[0], '/') != NULL)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		s->exit_status = 127;
		return ;
	}
	else if ((st.st_mode & !S_IRWXU) || (st.st_mode & S_IFDIR))
	{
		//ft_putstrs_fd("-bash: ", s->tokens[0], 0, 2);
		//ft_putstr_fd(s->tokens[0], 2);
		if (st.st_mode & !S_IRWXU)
		{
			ft_putstrs_fd("-bash: ", s->tokens[0], ": Permission denied\n", 2);
			//ft_putstr_fd(": Permission denied\n", 2);
			s->exit_status = 1;
		}
		else
		{
			ft_putstrs_fd("-bash: ", s->tokens[0], ": is a directory\n", 2);
			//ft_putstr_fd(": is a directory\n", 2);
			s->exit_status = 126;
		}
		return ;
	}
	ft_execute_command(s);
}

void	ft_process_tokken(t_minishell *s)
{
	int	i;

	i = 0;
	while (i < 7 && ft_strncmp(s->tokens[0], s->blt_cmds[i], \
		ft_strlen(s->blt_cmds[i]) + 1) != 0)
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
		blt_exit(s);
		//ft_clean_up(s);
		//exit(0);
	}
	else
		no_blt(s);
}

int	ft_check_for_pipes(t_minishell *s, int i)
{
	int	j;

	j = -1;
	while (s->commands[i][++j] != '\0')
	{
		if (s->commands[i][j] == '|')
			return (TRUE);
	}
	return (FALSE);
}

void	ft_process_command(t_minishell *s, int i)
{
	if (ft_check_for_pipes(s, i))
	{
		s->pipe_commands = special_split(s->commands[i], '|');
		ft_pipes(s);
		s->pipe_commands = ft_free_matrix(s->pipe_commands);
	}
	else
	{
		s->tokens = special_split(s->commands[i], ' ');
		check_env_var(s);
		if (check_redirections(s) == -1)
			return ;
		if (s->tokens[0])
		{
			ft_get_path(s);
			ft_process_tokken(s);
		}
		s->tokens = ft_free_matrix(s->tokens);
	}
}
