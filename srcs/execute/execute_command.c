#include "../../includes/minishell.h"

/*
** Function ft_execute_command() search if there is a command to execute in the
** s->command_path. If there is not such command, print error and returns.
** Other than that, creates a child process where tries to run the command using
** execve() function. On succes execve() doesn't return. If there is an error,
** errno is set, so error message can be printed.
** Parent process wait until child process is done. And using WEXITSTATUS set
** the return value from the command executed in the child process to be
** consulted with "echo $?" command.
*/

void	ft_execute_command(t_minishell *s)
{
	pid_t	child_pid;
	int		stat_loc;
	char	*path;
	int		ret;

	if (!s->command_path)
	{
		printf("-bash: %s: command not found\n", s->tokens[0]);
		s->exit_status = 127;
		return ;
	}
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
	child_pid = fork();
	if (child_pid < 0)
		ft_print_error(s);
	else if (child_pid == 0)
	{
		if (s->fd != 1)
		{
			dup2(s->fd, STDOUT_FILENO);
			close(s->fd);
		}
		if (s->fdi != 0)
		{
			dup2(s->fdi, STDIN_FILENO);
			close(s->fdi);
		}
		ret = execve(s->command_path, s->tokens, s->env);
		if (ret == -1)
			ft_print_error(s);
	}
	else
	{
		waitpid(child_pid, &stat_loc, WUNTRACED);
		s->exit_status = WEXITSTATUS(stat_loc);
	}
}

void	child_sig_handler(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}
