#include "../includes/minishell.h"

void	change_terminal_termios(t_minishell *s)
{
	static struct termios	oldt;
	static struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ft_read_line(s, s->n_cmds, '\0');
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\033[2D\033[0K", 2);
		write(1, "\n", 1);
		write(1, "$> ", 3);
		g_ln = ft_free_ptr(g_ln);
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\033[2D\033[0K", 2);
}

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	s;

	errno = 0;
	ft_initialize_variables(&s);
	ft_get_env_variables(&s, envp);
	while (TRUE)
	{
		write(1, "$> ", 3);
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
		change_terminal_termios(&s);
		if (g_ln[0] != '\0')
			ft_process_line(&s);
		if (g_ln != NULL)
			g_ln = ft_free_ptr(g_ln);
	}
	argc = 1;
	if (argv)
		free(argv);
	return (0);
}

void	ft_get_env_variables(t_minishell *s, char **envp)
{
	int	i;
	int	n;

	n = 0;
	while (envp[n])
		n++;
	s->env = (char **)malloc(sizeof(char *) * (n + 1));
	if (!s->env)
		ft_print_error(s);
	i = -1;
	while (++i < n)
		s->env[i] = ft_strdup(envp[i]);
	s->env[i] = NULL;
	i = ft_find_env_var(s, "HOME=");
	if (i >= 0)
		s->home = ft_strdup(s->env[i]);
	else
		s->home = NULL;
}

void	ft_initialize_variables(t_minishell *s)
{
	g_ln = NULL;
	s->env = NULL;
	s->tokens = NULL;
	s->commands = NULL;
	s->env_address = NULL;
	s->command_path = NULL;
	s->exit_status = 0;
	s->n_cmds = 0;
	s->history_cmds = NULL;
	s->new_hist_cmd = NULL;
	s->fd = 1;
	s->fdi = 0;
	s->blt_cmds = (char **)malloc(sizeof(char *) * (7 + 1));
	if (!s->blt_cmds)
		ft_print_error(s);
	s->blt_cmds[0] = ft_strdup("echo");
	s->blt_cmds[1] = ft_strdup("cd");
	s->blt_cmds[2] = ft_strdup("pwd");
	s->blt_cmds[3] = ft_strdup("export");
	s->blt_cmds[4] = ft_strdup("unset");
	s->blt_cmds[5] = ft_strdup("env");
	s->blt_cmds[6] = ft_strdup("exit");
	s->blt_cmds[7] = NULL;
}
