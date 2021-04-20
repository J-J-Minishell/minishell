// Isolate each command getting rid of useless characters (as initial o final spaces, duplicate spaces or ';' at the end).
// Split commands into tokens
// Make the environment variables expansion
// No leaks or errors so far


//////////////////////////////////////////////////////////
//														//
//   To do:   execute system commands with no pipes     //
//														//
//////////////////////////////////////////////////////////


// valgrind --leak-check=full \
// 			--show-leak-kinds=all \
// 			--track-origins=yes \
// 			--verbose \
// 			--log-file=valgrind-out.txt \
// 			./minishell

#include "../includes/minishell.h"

void	change_terminal_termios(t_minishell *s)
{
	static struct termios oldt;
	static struct termios newt;

	/* tcgetattr obtiene la configuración actual del terminal
	STDIN_FILENO se utiliza para escribir la configuración en oldt */
	tcgetattr( STDIN_FILENO, &oldt);
	/* se hace una copia de la configuración */
	newt = oldt;

	/* se deshabilita el flag ICANON */
	newt.c_lflag &= ~(ICANON);          

	/* se envia la nueva configuración a STDIN
	usamos TCSANOW para modificar la configuración. */
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	ft_read_line(s);

	/* se restaura la configuración original */
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\033[2D\033[0K", 2);
		write(1, "\n", 1);
		write(1, "$> ", 3);
		line = ft_free_ptr(line);
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\033[2D\033[0K", 2);
}

int		main(int argc, char *argv[], char **envp)
{
	t_minishell	s;

	errno = 0;										// Set errno value to 0
	ft_initialize_variables(&s);					// Initialice variables to NULL to freed them only if they have a real value
	ft_get_env_variables(&s, envp);					// Save all environment variables
	while (TRUE)
	{
		write(1, "$> ", 3);							// Print minishell prompt
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
		change_terminal_termios(&s);
		if (line[0] != '\0')
			ft_process_line(&s);						// Procces and execute commands
		if (line != NULL)
			line = ft_free_ptr(line);				// Freed 'line' between loop interactions
	}
	return (0);
}

void	ft_get_env_variables(t_minishell *s, char **envp)
{
	int			i;
	int			n;

	n = 0;
	while (envp[n])									// Count number of environment variables
		n++;
	if (!(s->env = (char **)malloc(sizeof(char *) * (n + 1))))		// Alloc memory to copy the environment variables...
		ft_print_error(s);											// ...from envp to an internal variable
	i = -1;
	while (++i < n)
		s->env[i] = ft_strdup(envp[i]);				// Copying external env. variables to my local env variable
	s->env[i] = NULL;
	i = ft_find_env_var(s, "HOME=");
	s->home = i >= 0 ? ft_strdup(s->env[i]) : NULL;
}

void	ft_initialize_variables(t_minishell *s)
{
	line = NULL;									// Initialize all this variables with NULL to setup a conditional free at...
	s->env = NULL;									// ...the end onĺy in case they now have a value
	s->tokens = NULL;								//
	s->commands = NULL;
	s->env_address = NULL;
	s->command_path = NULL;
	s->exit_status = 0;
	s->n_cmds = 0;
	s->history_cmds = NULL;
	s->new_hist_cmd = NULL;
	s->fd = 1;
	s->fdi = 0;
	if (!(s->blt_cmds = (char **)malloc(sizeof(char *) * (7 + 1))))
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

