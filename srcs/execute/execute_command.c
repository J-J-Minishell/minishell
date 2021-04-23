#include "../../includes/minishell.h"

void	ft_child_process(t_minishell *s)
{
	int	ret;

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

void	ft_execute_command(t_minishell *s)
{
	pid_t	child_pid;
	int		stat_loc;

	if (!s->command_path)
	{
		printf("-bash: %s: command not found\n",
			error_backslash_var(s, s->tokens[0]));
		s->exit_status = 127;
		return ;
	}
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
	child_pid = fork();
	if (child_pid < 0)
		ft_print_error(s);
	else if (child_pid == 0)
		ft_child_process(s);
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
