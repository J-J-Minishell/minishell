#include "minishell.h"

void	ft_execute_command(t_minishell *s)
{
	pid_t	child_pid;
	int		stat_loc;
	char	*path;

	//ft_get_path(s);    // Cambiado de sitio a la funcion ft_proccess_line
	child_pid = fork();
	if (child_pid < 0)
		ft_print_error(s);
	else if (child_pid == 0)
		execve(s->command_path, s->tokens, s->env);
	else
		waitpid(child_pid, &stat_loc, WUNTRACED);
}
