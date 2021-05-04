#include "../../includes/minishell.h"

void	switch_pipes(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(fds + 2);
}

void	process_son(t_minishell *s, int *fds, int *flag, int j)
{
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
	if (!fork())
	{
		s->flag_pipe = 1;
		if (!flag[0])
			dup2(fds[0], STDIN_FILENO);
		if (!flag[1])
			dup2(fds[3], STDOUT_FILENO);
		j = 0;
		while (j < 4)
			close(fds[j++]);
		check_env_var(s);
		if (check_redirections(s) != -1)
		{
			remove_token_quotes(s, 0);
			ft_get_path(s);
			ft_process_tokken(s);
		}
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

void	ft_pipes(t_minishell *s)
{
	int	i;
	int	fds[4];
	int	flag[2];
	int	sons;

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
		process_son(s, fds, flag, 0);
		sons++;
		flag[0] = 0;
		switch_pipes(fds);
		s->tokens = ft_free_matrix(s->tokens);
	}
	while (sons-- > 0)
		wait(&s->exit_status);
	close_fds(fds);
}
