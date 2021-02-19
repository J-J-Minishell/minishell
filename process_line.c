#include "minishell.h"

void	ft_process_tokken(t_minishell *s)
{
	int i;

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

void	ft_process_line(t_minishell *s)
{
	int i;

	s->commands = special_split(s->line, ';');
	i = 0;
	while (s->commands[i])
	{
		s->tokens = special_split(s->commands[i], ' ');
		check_env_var(s);
		ft_get_path(s);	// Cambiado por error al liberar command_path dos lineas mas abajo ya que se libera en cada vuelta del while pero solo se reservaba cuando no era blt
		ft_process_tokken(s);
		ft_free_ptr(s->command_path);
		ft_free_ptr(s->path); // Anadido
		ft_free_matrix(s->tokens);
		i++;
	}
	ft_free_matrix(s->commands);
}

