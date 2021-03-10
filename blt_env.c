#include "minishell.h"

void	blt_env(t_minishell *s)
{
	int 	i;

	i = 0;
	while (s->env[i])
	{
		ft_putstr_fd( s->env[i], 0);
		write(1, "\n", 1);
		i++;
	}
	s->exit_status = 0;
}
