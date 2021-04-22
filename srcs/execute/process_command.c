#include "../../includes/minishell.h"

/*
** This function is used when the command is not a builtin. It starts checking
** if the command exists. It uses stat() function to do that. Using stat() the
** info about the file it is saved on a struct that is used later to check the
** execution permissions.
** If the command doesn't exist error message is printed on stdout and exit
** status is set properly. If the command exists but doesn't have execution
** permission an error message is printed on stdout and exit status is set.
** Finally, if the command exists and have execution permission the function
** ft_execute_command() is called.
*/

void	no_blt(t_minishell *s)
{
	struct stat	st;

	if (stat(s->command_path, &st))
	{
		ft_putstr_fd("-bash: ", 0);
		ft_putstr_fd(s->tokens[0], 0);
		ft_putstr_fd(": No such file or directory\n", 0);
		s->exit_status = 127;
		return ;
	}
	else
	{
		if (st.st_mode & !S_IRWXU)
		{
			ft_putstr_fd("-bash: ", 0);
			ft_putstr_fd(s->tokens[0], 0);
			ft_putstr_fd(": Permission denied\n", 0);
			s->exit_status = 126;
			return ;
		}
		ft_execute_command(s);
	}
}

/*
** This function compares the first token (the one that stores the command)
** whit the array of strings containing the builtin commands. If it gets a
** match, it calls the apropiate function. If there is no coincidence, it
** calls no_blt() function, in order to execute a non builtin command.
*/

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
		ft_clean_up(s);
		exit(0);
	}
	else
		no_blt(s);
}

/*
** This function go through the string where the command is stored in order to
** locate pipe marks '|'. It returns if a pipe was located or not.
*/

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

/*
** This function first use ft_check_for_pipes() to know if there are pipes that
** it should manage. If the answer is yes, split the command line using pipe
** mark as separator and stores the result in a string array inside the main
** struct. Then it calls the function in charge of manage pipes.
** If there is no pipes, first split the command into tokens using blank space
** as separator. Then calls check_env_var() to make the proper variable
** expansion if it is needed. Next it calls check_redirections() to take care
** of the in and out redirections. After finish all that calls ft_get_path() to
** get the complete path to the command. And finally calls the function
** ft_process_token() where the command will be executed.
** After the command has been executed the function free the string array of
** tokens.
*/

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
		check_redirections(s);
		if (s->tokens[0])
		{
			ft_get_path(s);
			ft_process_tokken(s);
		}
		s->tokens = ft_free_matrix(s->tokens);
	}
}
