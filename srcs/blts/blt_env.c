#include "../../includes/minishell.h"

/*
** Simple function that goes over all the environment variables and get them
** printed.
*/

void	blt_env(t_minishell *s)
{
	int	i;

	i = 0;
	while (s->env[i])
	{
		ft_putstr_fd(s->env[i], s->fd);
		write(s->fd, "\n", 1);
		i++;
	}
	s->exit_status = 0;
}
