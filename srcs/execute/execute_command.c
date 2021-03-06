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

	child_pid = 0;
	if (!s->flag_pipe)
	{
		child_pid = fork();
		signal(SIGINT, child_sig_handler);
		signal(SIGQUIT, child_sig_handler);
	}
	if (child_pid < 0)
		ft_print_error(s);
	else if (child_pid == 0 || s->flag_pipe)
		ft_child_process(s);
	else
	{
		waitpid(child_pid, &stat_loc, WUNTRACED);
		s->exit_status = WEXITSTATUS(stat_loc);
		check_signal(s, 1);
	}
}

void	child_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_ln = ft_free_ptr(g_ln);
		g_ln = ft_strdup("ctrl^C");
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_ln = ft_free_ptr(g_ln);
		g_ln = ft_strdup("ctrl^\\");
	}
}
