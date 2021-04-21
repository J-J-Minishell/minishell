#include "../../includes/minishell.h"

/*
** cambia el segundo pipe al primero.
** cierra el primer pipe y cambia los fds del segundo al primero
** luego crea un nuevo pipe en donde estaba el segundo
*/
void	switch_pipes(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(fds + 2);
}

/*
** solo entra en el if el hijo del fork.
** PRIMERA VEZ:
** la primera vez que entra en esta funcion flag[0] = 1 porque es el primer comando
** y flag[1] = 0 porque no es el ultimo comando. Entonces solo entra en el segundo if
** cambiando el STDOUT_FILENO por el del segundo pipe.
** ENTRE MEDIAS:
** el resto de veces entra en los dos if cambiando el STDIN_FILENO por la salida del anterior comando
** y el STDOUT_FILENO por el del segundo pipe igual.
** ULTIMA:
** en la ultima solo cambia el STDIN_FILENO por la salida del anterior comando
*/
void	process_son(t_minishell *s, int *fds, int *flag)
{
	int	j;

	if (!fork())
	{
		if (!flag[0])
			dup2(fds[0], STDIN_FILENO);
		if (!flag[1])
			dup2(fds[3], STDOUT_FILENO);
		j = 0;
		while (j < 4)
			close(fds[j++]);
		check_env_var(s);
		check_redirections(s);
		ft_get_path(s);
		ft_process_tokken(s);
		ft_clean_up(s);
		s->pipe_commands = ft_free_matrix(s->pipe_commands);
		s->command_path = ft_free_ptr(s->command_path);
		exit(s->exit_status);
	}
}

void	close_fds(int *fds)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		close(fds[i]);
		i++;
	}
}

/*
** al principìo crea dos pipes, fds[0] fds[1] y fds[2] fds[3]
** flag[0] vale 1 si es el primer comando del primer pipe, si no, vale 0 (linea 91).
** flag[1] vale 0 salvo si es el ultimo comando del ultimo pipe, que entonces vale 1 (linea 87, 88).
** sons incrementa en uno cada vez que se hace un fork y luego al final por cada fork que se haya hecho
** hace un wait para esperar a que haya terminado el proceso.
*/
void	ft_pipes(t_minishell *s)
{
	int i;
	int fds[4];
	int flag[2];
	int sons;

	pipe(fds);
	pipe(fds + 2);
	i = -1;
	flag[0] = 1;
	flag[1] = 0;
	sons = 0;
	while (s->pipe_commands[++i])
	{
		s->tokens = special_split(s->pipe_commands[i], ' ');
		if (!s->pipe_commands[i + 1])
			flag[1] = 1;
		process_son(s, fds, flag);
		sons++;
		flag[0] = 0;
		switch_pipes(fds);
		s->tokens = ft_free_matrix(s->tokens);
	}
	while (sons-- > 0)
		wait(&s->exit_status);
	close_fds(fds);
}
